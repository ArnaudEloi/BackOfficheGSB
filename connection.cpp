#include "connection.h"
#include "ui_connection.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Connection::Connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);
    isConnect=false;
    ui->labelError->setVisible(false);
    ui->lineEditMDP->setEchoMode(QLineEdit::Password);

}

Connection::~Connection()
{
    delete ui;
}

void Connection::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Connection::on_pushButtonConnect_clicked()
{
    QSqlQuery res("select login, mdp from userBackOffice where login='"+ui->lineEditLogin->text()+"' and mdp='"+ui->lineEditMDP->text()+"';");
qDebug()<<"select login, mdp from userBackOffice where login='"+ui->lineEditLogin->text()+"' and mdp='"+ui->lineEditMDP->text()+"';";
    res.first();
    qDebug()<<res.value(1);
    if(res.isNull(0))
    {
        qDebug()<<"echec de connection";
        isConnect=false;
        ui->labelError->setVisible(true);
        ui->lineEditLogin->clear();
        ui->lineEditMDP->clear();
    }
    else
    {
        qDebug()<<"connection réussi";
        isConnect=true;
        this->close();
    }
}

QString Connection::getLogin()
{
    return this->ui->lineEditLogin->text();
}

void Connection::on_pushButtonAnnuler_clicked()
{
    this->close();
}
