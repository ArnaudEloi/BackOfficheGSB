#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
    class Connection;
}

class Connection : public QDialog {
    Q_OBJECT
public:
    Connection(QWidget *parent = 0);
    ~Connection();
    bool isConnect;
    QString getLogin();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Connection *ui;


private slots:


private slots:
    void on_pushButtonAnnuler_clicked();
    void on_pushButtonConnect_clicked();

};

#endif // CONNECTION_H
