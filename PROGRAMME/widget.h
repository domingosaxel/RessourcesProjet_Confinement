#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QCamera>
#include <QCameraImageCapture>
#include "lecteurcarte.h"
#include <QCameraInfo>
#include <QCameraViewfinderSettings>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QFileInfo>

#define PRENOM "AXEL"
#define NOM "DOMINGOS"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void deleteOldFiles();

private slots:
    void on_nouvelle_carte();

    void on_pushButtonCaptureCasier_clicked();

    void on_pushButtonCaptureUtilisateur_clicked();

    void onTime_timeout();

private:
    Ui::Widget *ui;

    LecteurCarte leLecteur;
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    QCamera *camera2;
    QCameraImageCapture *imageCapture2;
    QTimer time;
    QDate Date;
    QFile file;
};
#endif // WIDGET_H
