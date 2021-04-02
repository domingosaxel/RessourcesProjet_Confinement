#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <QObject>
#include "QTimer"
#include "wiegand.h"


class LecteurCarte : public QObject
{
    Q_OBJECT
public:
    explicit LecteurCarte(QObject *parent = nullptr);
     ~LecteurCarte();
    QByteArray lireTagNFC();

private slots:
    void onTimerTempo_timeout();

private:
    QTimer timer;
    QByteArray code;
    Wiegand protocole;

    signals:
    void nouvelle_carte();
};

#endif // LECTEURCARTE_H
