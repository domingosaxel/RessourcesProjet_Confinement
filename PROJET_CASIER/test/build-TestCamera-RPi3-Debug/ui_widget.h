/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButtonUtilisateur;
    QPushButton *pushButtonQuitter;
    QPushButton *pushButtonCasier;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(400, 300);
        pushButtonUtilisateur = new QPushButton(Widget);
        pushButtonUtilisateur->setObjectName(QStringLiteral("pushButtonUtilisateur"));
        pushButtonUtilisateur->setGeometry(QRect(70, 120, 80, 24));
        pushButtonQuitter = new QPushButton(Widget);
        pushButtonQuitter->setObjectName(QStringLiteral("pushButtonQuitter"));
        pushButtonQuitter->setGeometry(QRect(120, 170, 80, 24));
        pushButtonCasier = new QPushButton(Widget);
        pushButtonCasier->setObjectName(QStringLiteral("pushButtonCasier"));
        pushButtonCasier->setGeometry(QRect(160, 120, 80, 24));

        retranslateUi(Widget);
        QObject::connect(pushButtonQuitter, SIGNAL(clicked()), Widget, SLOT(close()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButtonUtilisateur->setText(QApplication::translate("Widget", "Utilisateur", nullptr));
        pushButtonQuitter->setText(QApplication::translate("Widget", "Quitter", nullptr));
        pushButtonCasier->setText(QApplication::translate("Widget", "Casier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
