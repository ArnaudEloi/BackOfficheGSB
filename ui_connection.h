/********************************************************************************
** Form generated from reading UI file 'connection.ui'
**
** Created: Thu Oct 31 12:35:24 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTION_H
#define UI_CONNECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Connection
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditMDP;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelError;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonAnnuler;

    void setupUi(QDialog *Connection)
    {
        if (Connection->objectName().isEmpty())
            Connection->setObjectName(QString::fromUtf8("Connection"));
        Connection->resize(288, 126);
        Connection->setMinimumSize(QSize(288, 126));
        Connection->setMaximumSize(QSize(288, 126));
        QPalette palette;
        Connection->setPalette(palette);
        Connection->setAutoFillBackground(true);
        gridLayout = new QGridLayout(Connection);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(Connection);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAutoFillBackground(false);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(Connection);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEditLogin = new QLineEdit(Connection);
        lineEditLogin->setObjectName(QString::fromUtf8("lineEditLogin"));
        lineEditLogin->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 212, 212);"));
        lineEditLogin->setFrame(false);

        verticalLayout->addWidget(lineEditLogin);

        lineEditMDP = new QLineEdit(Connection);
        lineEditMDP->setObjectName(QString::fromUtf8("lineEditMDP"));
        lineEditMDP->setEnabled(true);
        QFont font;
        font.setStrikeOut(false);
        lineEditMDP->setFont(font);
        lineEditMDP->setAutoFillBackground(false);
        lineEditMDP->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 212, 212);"));
        lineEditMDP->setFrame(false);

        verticalLayout->addWidget(lineEditMDP);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        labelError = new QLabel(Connection);
        labelError->setObjectName(QString::fromUtf8("labelError"));
        labelError->setEnabled(true);
        labelError->setMinimumSize(QSize(0, 15));
        labelError->setMaximumSize(QSize(16777215, 15));
        QFont font1;
        font1.setItalic(true);
        labelError->setFont(font1);
        labelError->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        labelError->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(labelError);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonConnect = new QPushButton(Connection);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));
        pushButtonConnect->setDefault(true);
        pushButtonConnect->setFlat(false);

        horizontalLayout_2->addWidget(pushButtonConnect);

        pushButtonAnnuler = new QPushButton(Connection);
        pushButtonAnnuler->setObjectName(QString::fromUtf8("pushButtonAnnuler"));
        pushButtonAnnuler->setEnabled(true);
        pushButtonAnnuler->setFlat(false);

        horizontalLayout_2->addWidget(pushButtonAnnuler);


        verticalLayout_4->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 0, 1, 1);


        retranslateUi(Connection);

        QMetaObject::connectSlotsByName(Connection);
    } // setupUi

    void retranslateUi(QDialog *Connection)
    {
        Connection->setWindowTitle(QApplication::translate("Connection", "Connection", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Connection", "Login :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Connection", "Mot de passe :", 0, QApplication::UnicodeUTF8));
        labelError->setText(QApplication::translate("Connection", "Login ou mot de passe incorrect", 0, QApplication::UnicodeUTF8));
        pushButtonConnect->setText(QApplication::translate("Connection", "Connection", 0, QApplication::UnicodeUTF8));
        pushButtonAnnuler->setText(QApplication::translate("Connection", "Annuler", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Connection: public Ui_Connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTION_H
