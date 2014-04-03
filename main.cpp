#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QBitmap>
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>
#include <QDesktopWidget>
#include "connection.h"
#include <QLibraryInfo>
#include <QTranslator>

int main(int argc, char *argv[])
{

    // CONNECTION
    // prise en compte de l'utf8 pour les chaine en dur pour le code
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // connexion à la base
    QSqlDatabase baseGSB=QSqlDatabase::addDatabase("QMYSQL");
    baseGSB.setHostName("localhost");
    baseGSB.setUserName("Arnaud");
    baseGSB.setPassword("ini01");
    baseGSB.setDatabaseName("db_gestioncr");
    if(baseGSB.open())
    {
        QApplication a(argc, argv);

        QString locale = QLocale::system().name().section('_', 0, 0);
        QTranslator translator;
        translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        a.installTranslator(&translator);

        QPixmap image(":/new/img/gsb2.png");
        QSplashScreen gsb(image);
        gsb.setMask(QRegion(image.mask()));
        gsb.setPixmap(image);

        gsb.show();
        gsb.setEnabled(false);

        sleep(1);

        Connection c;
        c.setWindowFlags(Qt::FramelessWindowHint);
        QDesktopWidget bureau;
        QRect ecran=bureau.screenGeometry();
        int x=ecran.width()/2 - c.width()/2;
        int y=ecran.height()/2 - c.height()/2;
        c.move(x,y);

        c.show();
        a.exec();

        if(c.isConnect)
        {
            gsb.hide();
            MainWindow w(0,c.getLogin());
            x=ecran.width()/2 - w.width()/2;
            y=ecran.height()/2 - w.height()/2;
            w.move(x,y);
            w.show();
            return a.exec();
        }

    }
    else
    {
        qDebug()<<"Erreur 607: connexion refused";
    }
}
