#include "lecteurcarte.h"
#include <QDebug>
#include "widget.h"
#include "ui_widget.h"

LecteurCarte::LecteurCarte(QObject *parent) : QObject(parent)
      , protocole(D0_PIN, D1_PIN)
{
    timer.setSingleShot(true);
    connect(&timer,&QTimer::timeout,this,&LecteurCarte::onTimerTempo_timeout);
    timer.start(500);
}

LecteurCarte::~LecteurCarte()
{

}

QByteArray LecteurCarte::lireTagNFC()
{
    return code;
}

void LecteurCarte::onTimerTempo_timeout()
{
    int bitLen = protocole.wiegandGetPendingBitCount();
    if (bitLen == 0)
        timer.start(500);
    else
    {
        char data[100];
        bitLen = protocole.wiegandReadData((void *)data, 100);
        int bytes = bitLen / 8 + 1;
        qDebug() <<  bitLen << " " << bytes;
        for (int i = 0; i < bytes; i++)
        {
            code.push_front(data[i]);
        }
        emit nouvelle_carte();
        timer.start(500);
    }
}
