#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QString>
#include "extern_vars.h"
#include <QApplication>
#include <QScreen>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QDebug>
#include <QObject>

namespace Ui {
class welcome;
}

class welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();
    int h, w;
    void update_screen();
    void registrationInServer(QString postData);

private slots:
    void on_pushButton_clicked();
    void replyFinish(QNetworkReply*);

    void on_phoneNumber_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void next_button();
    void screen_updated();

private:
    Ui::welcome *ui;
};

#endif // WELCOME_H
