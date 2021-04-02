#ifndef WIEGAND_H
#define WIEGAND_H

#define D0_PIN 0
#define D1_PIN 1

#define WIEGANDMAXDATA 32
#define WIEGANDTIMEOUT 3000000

void data0Pulse(void);
void data1Pulse(void);
void wiegandInit(int d0pin, int d1pin);
void wiegandReset();
int wiegandGetPendingBitCount();
int wiegandReadData(void* data, int dataMaxLen);


#endif // WIEGAND_H
