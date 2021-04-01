#include "widget.h"
#include "ui_widget.h"
#include "wiegand_c.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)

{
    ui->setupUi(this);
    connect(&leLecteur,&LecteurCarte::nouvelle_carte,this,&Widget::on_nouvelle_carte);
    connect(&time,&QTimer::timeout,this,&Widget::onTime_timeout);
    time.setSingleShot(true);

    QCameraViewfinderSettings viewfinderSettings;
    viewfinderSettings.setResolution(1280, 720);
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    camera = new QCamera(cameras.at(0));
    camera->setViewfinderSettings(viewfinderSettings);
    qDebug() << cameras.at(0);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    imageCapture = new QCameraImageCapture(camera);
    camera->start();

    //camera2 = new QCamera(cameras.at(0));
    //camera2->setViewfinderSettings(viewfinderSettings);
    //qDebug() << cameras.at(0);
    //camera2->setCaptureMode(QCamera::CaptureStillImage);
    imageCapture2 = new QCameraImageCapture(camera);
    //camera2->start();
}


Widget::~Widget()
{
    delete ui;
    delete camera;
    delete camera2;
    delete imageCapture;
    delete imageCapture2;
}

void Widget::deleteOldFiles()
{
  /* if (file.exists()) {
        QDate today = QDate::currentDate();
        QFile lastModified = QFileInfo::lastModified();

        int diffInDays = (int)( (today.currentDate() - file.lastModified()) /(1000 * 60 * 60 * 24) );
        if(diffInDays>14){
            qDebug() << "File is two week old";
            //you can delete the file here
            file.remove();
        }
    }*/
}

void Widget::on_nouvelle_carte()
{
    QByteArray leTag = leLecteur.lireTagNFC();
    ui->lineEditCode->setText(leTag.toHex().toUpper());
    qDebug() << "numero carte :" << leTag.toHex().toUpper();
    on_pushButtonCaptureUtilisateur_clicked();
}

void Widget::on_pushButtonCaptureUtilisateur_clicked()
{       
    QDateTime now = QDateTime::currentDateTime();
    QString nom = NOM;
    QString prenom = PRENOM;
    QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));
    QString filename = QString::fromLatin1("/home/pi/%1-%2-%3-UTILISATEUR.jpg").arg(nom).arg(prenom).arg(timestamp);
    QFile file(filename);

    imageCapture->capture(filename);
    qDebug() << "chemin :" << qApp->applicationDirPath();
    time.start(500);
    ui->pushButtonCaptureUtilisateur->setEnabled(0);
    ui->pushButtonCaptureCasier->setEnabled(0);
}

void Widget::on_pushButtonCaptureCasier_clicked()
{    
    QDateTime now = QDateTime::currentDateTime();
    QString nom = NOM;
    QString prenom = PRENOM;
    QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));
    QString filename = QString::fromLatin1("/home/pi/%1-%2-%3-CASIER.jpg").arg(nom).arg(prenom).arg(timestamp);
    QFile file(filename);

    imageCapture->capture(filename);
    qDebug() << "chemin :" << qApp->applicationDirPath();
    time.start(500);
    ui->pushButtonCaptureCasier->setEnabled(0);
    ui->pushButtonCaptureUtilisateur->setEnabled(0);
}

void Widget::onTime_timeout()
{
    ui->pushButtonCaptureCasier->setEnabled(1);
    ui->pushButtonCaptureUtilisateur->setEnabled(1);
    time.stop();
}
