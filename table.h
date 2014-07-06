#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QScreen>
#include <QRect>
#include <QApplication>
#include <QNetworkReply>
#include "extern_vars.h"

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0);
    ~table();
    int h, w;
    QString getHttp();
    void parserJSON(QString httpResponse);
    QNetworkAccessManager * pManager;

private slots:
    void on_pushButton_clicked();
    void update_screen();
    void updateHTTP();
    void replyFinish(QNetworkReply*);
    void on_p00_03_clicked();
    void on_p03_06_clicked();
    void on_p06_09_clicked();
    void on_p09_12_clicked();
    void on_p12_15_clicked();
    void on_p15_18_clicked();
    void on_p18_21_clicked();
    void on_p21_24_clicked();
    void standToQueue(QString time);//обобщаем все нажатия. При нажатии вызываем только одну функцию.

signals:
    void prev_button();

private:
    Ui::table *ui;
};

#endif // TABLE_H
