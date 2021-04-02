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

    qDebug() << " ";
    qDebug() << "cameras disponibles : ";
    camera = new QCamera(cameras.at(0));
    camera->setViewfinderSettings(viewfinderSettings);
    qDebug() <<cameras.at(0);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    imageCapture = new QCameraImageCapture(camera);
    camera->start();

    qDebug() << " ";
    camera2 = new QCamera(cameras.at(1));
    camera2->setViewfinderSettings(viewfinderSettings);
    qDebug() << cameras.at(1);
    camera2->setCaptureMode(QCamera::CaptureStillImage);
    imageCapture = new QCameraImageCapture(camera);
    camera2->start();


    for(const QCameraInfo &cameraInfo : cameras)
    {
        qDebug() << " ";
        qDebug() << "nom de la camera : " << cameraInfo.deviceName();
        qDebug() << "position de la camera : " << cameraInfo.position();
        qDebug() << "description de la caméra : "<<cameraInfo.description();
    }
    qDebug() << " ";
    qDebug() << "camera par default : " << QCameraInfo::defaultCamera();
    qDebug() << " ";
}

QString nom = NOM;
QString prenom = PRENOM;
QDateTime now = QDateTime::currentDateTime();
QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));

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
    const QDate today = QDate::currentDate();
    const QString path = QCoreApplication::applicationDirPath() + "/jpg/";

    QString filter(nom+"-"+prenom+"-"); // patern du nom des images
    filter = filter.arg("[0123456789]"); // valid characters
    //filter = filter.arg(timestamp );
    qDebug() << "filtre : " << filter;

    Q_FOREACH (auto fileInfo, QDir(path).entryInfoList(QStringList(filter), QDir::Files)) {
        if (fileInfo.birthTime().date().daysTo(today) > 14) {
            QString filepath = fileInfo.absoluteFilePath();
            QDir deletefile;
            deletefile.setPath(filepath);
            deletefile.remove(filepath);
            qDebug() << "File " + filepath + " is deleted!";
        }
    }
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
    QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));
    QString filename = QString::fromLatin1("/home/pi/%1-%2-%3-UTILISATEUR.jpg").arg(nom).arg(prenom).arg(timestamp);
    QFile file(filename);

    imageCapture->capture(filename);
    qDebug() << "chemin :" << qApp->applicationDirPath();
    time.start(1000);
    ui->pushButtonCaptureUtilisateur->setEnabled(0);
    ui->pushButtonCaptureCasier->setEnabled(0);
}

void Widget::on_pushButtonCaptureCasier_clicked()
{    
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));
    QString filename = QString::fromLatin1("/home/pi/%1-%2-%3-CASIER.jpg").arg(nom).arg(prenom).arg(timestamp);
    QFile file(filename);


    imageCapture->capture(filename);
    qDebug() << "chemin :" << qApp->applicationDirPath();
    time.start(1000);
    ui->pushButtonCaptureCasier->setEnabled(0);
    ui->pushButtonCaptureUtilisateur->setEnabled(0);
}

void Widget::onTime_timeout()
{
    ui->pushButtonCaptureCasier->setEnabled(1);
    ui->pushButtonCaptureUtilisateur->setEnabled(1);
    time.stop();
}

void Widget::on_pushButtonSupprimer_clicked()
{
    deleteOldFiles();
}
