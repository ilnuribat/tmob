#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonValueRef>

namespace Ui {
class getTable;
}

class getTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit getTable(QWidget *parent = 0);
    ~getTable();
    QTimer *timer;
    QString httpResponse;
    QString getHttp();
    QJsonObject qJSon;
    QJsonDocument qJSDoc;
    QVariantMap qVarMap;
    void parser();

private slots:
    void update();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void getReplyFinished();
    void readyReadReply();
    void on_toolButton_clicked();
    void replyFinish();

    void on_time_00_03_linkActivated(const QString &link);

    void on_button_00_03_clicked();

    void on_centralWidget_destroyed();

private:
    int count;
    Ui::getTable *ui;

};

#endif // MAINWINDOW_H
