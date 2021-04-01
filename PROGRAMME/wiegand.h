#ifndef WIEGAND_H
#define WIEGAND_H

#define D0_PIN 0
#define D1_PIN 1

#define WIEGANDMAXDATA 32
#define WIEGANDTIMEOUT 3000000

#include <QObject>

class Wiegand : public QObject
{
    Q_OBJECT
public:
    explicit Wiegand(int d0pin, int d1pin, QObject *parent = nullptr);
    static void data0Pulse(void);
    static void data1Pulse(void);
    void wiegandInit(int d0pin, int d1pin);
    void wiegandReset();
    int wiegandGetPendingBitCount();
    int wiegandReadData(void* data, int dataMaxLen);

signals:

};

#endif // WIEGAND_H
