/********************************************************************************
** Form generated from reading UI file 'compression.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPRESSION_H
#define UI_COMPRESSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_compression
{
public:
    QWidget *centralWidget;
    QPushButton *zip;
    QPushButton *unzip;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *compression)
    {
        if (compression->objectName().isEmpty())
            compression->setObjectName(QString::fromUtf8("compression"));
        compression->resize(424, 200);
        centralWidget = new QWidget(compression);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        zip = new QPushButton(centralWidget);
        zip->setObjectName(QString::fromUtf8("zip"));
        zip->setGeometry(QRect(50, 60, 111, 41));
        unzip = new QPushButton(centralWidget);
        unzip->setObjectName(QString::fromUtf8("unzip"));
        unzip->setGeometry(QRect(250, 60, 111, 41));
        compression->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(compression);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 424, 28));
        compression->setMenuBar(menuBar);
        statusBar = new QStatusBar(compression);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        compression->setStatusBar(statusBar);

        retranslateUi(compression);

        QMetaObject::connectSlotsByName(compression);
    } // setupUi

    void retranslateUi(QMainWindow *compression)
    {
        compression->setWindowTitle(QCoreApplication::translate("compression", "compression", nullptr));
        zip->setText(QCoreApplication::translate("compression", "\345\216\213\347\274\251", nullptr));
        unzip->setText(QCoreApplication::translate("compression", "\350\247\243\345\216\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class compression: public Ui_compression {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPRESSION_H
