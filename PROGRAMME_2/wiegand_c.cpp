/*
 * Wiegand API Raspberry Pi
 * By Kyle Mallory All rights reserved.
 * 12/01/2013
 * Based on previous code by Daniel Smith (www.pagemac.com) and Ben Kent (www.pidoorman.com)
 * Depends on the wiringPi library by Gordon Henterson: https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 * This is linked with -lpthread -lwiringPi -lrt
 *
 * The Wiegand interface has two data lines, DATA0 and DATA1.  These lines are normall held
 * high at 5V.  When a 0 is sent, DATA0 drops to 0V for a few µs.  When a 1 is sent, DATA1 drops
 * to 0V for a few µs. There are a few ms between the pulses.
 *
 *   *************
 *   * IMPORTANT *
 *   *************
 *
 *   The Raspberry Pi GPIO pins are 3.3V, NOT 5V. Please take appropriate precautions to bring the
 *   5V Data 0 and Data 1 voltges down. I used a 330 ohm resistor and 3V3 Zenner diode for each
 *   connection. FAILURE TO DO THIS WILL PROBABLY BLOW UP THE RASPBERRY PI!
 *
 */


#include <wiringPi.h>
#include <time.h>
#include <unistd.h>
#include <memory.h>
#include "wiegand_c.h"


static unsigned char __wiegandData[WIEGANDMAXDATA];    // can capture upto 32 bytes of data -- FIXME: Make this dynamically allocated in init?
static unsigned long __wiegandBitCount;                // number of bits currently captured
static struct timespec __wiegandBitTime;               // timestamp of the last bit received (used for timeouts)

void data0Pulse(void) {
    if (__wiegandBitCount / 8 < WIEGANDMAXDATA)
    {
        __wiegandData[__wiegandBitCount / 8] <<= 1;
        __wiegandBitCount++;
    }
    clock_gettime(CLOCK_MONOTONIC, &__wiegandBitTime);
}

void data1Pulse(void) {
    if (__wiegandBitCount / 8 < WIEGANDMAXDATA)
    {
        __wiegandData[__wiegandBitCount / 8] <<= 1;
        __wiegandData[__wiegandBitCount / 8] |= 1;
        __wiegandBitCount++;
    }
    clock_gettime(CLOCK_MONOTONIC, &__wiegandBitTime);
}

void wiegandInit(int d0pin, int d1pin) {

    wiringPiSetup() ;
    pinMode(d0pin, INPUT);
    pinMode(d1pin, INPUT);

    wiringPiISR(d0pin, INT_EDGE_FALLING, data0Pulse);
    wiringPiISR(d1pin, INT_EDGE_FALLING, data1Pulse);
}

void wiegandReset() {
    memset((void *)__wiegandData, 0, WIEGANDMAXDATA);
    __wiegandBitCount = 0;
}

int wiegandGetPendingBitCount() {
    struct timespec now, delta;
    clock_gettime(CLOCK_MONOTONIC, &now);
    delta.tv_sec = now.tv_sec - __wiegandBitTime.tv_sec;
    delta.tv_nsec = now.tv_nsec - __wiegandBitTime.tv_nsec;

    if ((delta.tv_sec > 1) || (delta.tv_nsec > WIEGANDTIMEOUT))
        return __wiegandBitCount;

    return 0;
}

/*
 * wiegandReadData is a simple, non-blocking method to retrieve the last code
 * processed by the API.
 * data : is a pointer to a block of memory where the decoded data will be stored.
 * dataMaxLen : is the maximum number of -bytes- that can be read and stored in data.
 * Result : returns the number of -bits- in the current message, 0 if there is no
 * data available to be read, or -1 if there was an error.
 * Notes : this function clears the read data when called. On subsequent calls,
 * without subsequent data, this will return 0.
 */
 
int wiegandReadData(void* data, int dataMaxLen) {
    if (wiegandGetPendingBitCount() > 0) {
        int bitCount = __wiegandBitCount;
        int byteCount = (__wiegandBitCount / 8) + 1;
        memcpy(data, (void *)__wiegandData, ((byteCount > dataMaxLen) ? dataMaxLen : byteCount));

        wiegandReset();
        return bitCount;
    }
    return 0;
}



