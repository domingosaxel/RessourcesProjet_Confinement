#include "wiegand.h"
#include <wiringPi.h>
#include <time.h>
#include <unistd.h>
#include <memory.h>

static unsigned char __wiegandData[WIEGANDMAXDATA];    // can capture upto 32 bytes of data -- FIXME: Make this dynamically allocated in init?
static unsigned long __wiegandBitCount;                // number of bits currently captured
static struct timespec __wiegandBitTime;

Wiegand::Wiegand(int d0pin, int d1pin, QObject *parent) : QObject(parent)
{  
    wiringPiSetup() ;
    pinMode(d0pin, INPUT);
    pinMode(d1pin, INPUT);

    wiringPiISR(d0pin, INT_EDGE_FALLING, data0Pulse);
    wiringPiISR(d1pin, INT_EDGE_FALLING, data1Pulse);
}

void Wiegand::data0Pulse()
{
    if (__wiegandBitCount / 8 < WIEGANDMAXDATA)
    {
        __wiegandData[__wiegandBitCount / 8] <<= 1;
        __wiegandBitCount++;
    }
    clock_gettime(CLOCK_MONOTONIC, &__wiegandBitTime);
}

void Wiegand::data1Pulse()
{
    if (__wiegandBitCount / 8 < WIEGANDMAXDATA)
    {
        __wiegandData[__wiegandBitCount / 8] <<= 1;
        __wiegandData[__wiegandBitCount / 8] |= 1;
        __wiegandBitCount++;
    }
    clock_gettime(CLOCK_MONOTONIC, &__wiegandBitTime);
}

void Wiegand::wiegandReset()
{
    memset((void *)__wiegandData, 0, WIEGANDMAXDATA);
    __wiegandBitCount = 0;
}

int Wiegand::wiegandGetPendingBitCount()
{
    struct timespec now, delta;
    clock_gettime(CLOCK_MONOTONIC, &now);
    delta.tv_sec = now.tv_sec - __wiegandBitTime.tv_sec;
    delta.tv_nsec = now.tv_nsec - __wiegandBitTime.tv_nsec;

    if ((delta.tv_sec > 1) || (delta.tv_nsec > WIEGANDTIMEOUT))
        return __wiegandBitCount;

    return 0;
}

int Wiegand::wiegandReadData(void *data, int dataMaxLen)
{
    if (wiegandGetPendingBitCount() > 0) {
        int bitCount = __wiegandBitCount;
        int byteCount = (__wiegandBitCount / 8) + 1;
        memcpy(data, (void *)__wiegandData, ((byteCount > dataMaxLen) ? dataMaxLen : byteCount));

        wiegandReset();
        return bitCount;
    }
    return 0;
}
