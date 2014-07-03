#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QString>
#include "extern_vars.h"

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


private slots:
    void on_pushButton_clicked();
    void replyFinish(QNetworkReply*);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

signals:
    void next_button();
    void screen_updated();

private:
    Ui::welcome *ui;
};

#endif // WELCOME_H
