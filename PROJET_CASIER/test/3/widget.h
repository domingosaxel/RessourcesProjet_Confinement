#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraImageCapture>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonCasier_clicked();

    void on_pushButtonUtilisateur_clicked();

private:
    Ui::Widget *ui;

    QCamera *camera;
    QCamera *camera2;
    QCameraImageCapture *imageCapture;
    QCameraImageCapture *imageCapture2;

};

#endif // WIDGET_H
