#include "widget.h"
#include "ui_widget.h"
#include <QCameraInfo>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    camera = new QCamera(cameras.at(0));
    qDebug() << cameras.at(0);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    imageCapture = new QCameraImageCapture(camera);
    camera->start();

    camera2 = new QCamera(cameras.at(0));
    qDebug() << cameras.at(0);
    camera2->setCaptureMode(QCamera::CaptureStillImage);
    imageCapture2 = new QCameraImageCapture(camera2);
    camera2->start();
}

Widget::~Widget()
{
    delete ui;
    delete camera;
    delete camera2;
    delete imageCapture;
    delete imageCapture2;
}

void Widget::on_pushButtonCasier_clicked()
{
        imageCapture->capture("/home/pi/imageCasier.jpg");
}

void Widget::on_pushButtonUtilisateur_clicked()
{
        imageCapture->capture("/home/pi/imageUtilisateur.jpg");
}
