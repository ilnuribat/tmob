#include "welcome.h"
#include "ui_welcome.h"
#include <QApplication>
#include <QScreen>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QDebug>
#include <QObject>

welcome::welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    update_screen();

}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_clicked()
{
    if(HUMAN == "unDefined")
    {
        ui->label_2->setText("Выберите пункт - пассажир или водитель");
        return;
    }

    emit next_button();
    this->hide();
}

void welcome::update_screen()
{
    h= QApplication::primaryScreen()->availableSize().height();
    w= QApplication::primaryScreen()->availableSize().width();
    ui->verticalLayoutWidget->setGeometry(QRect(0, 0, w, h));
}

void welcome::replyFinish(QNetworkReply*)
{
}

void welcome::on_radioButton_clicked()
{
    HUMAN = "passanger_count";
}

void welcome::on_radioButton_2_clicked()
{
    HUMAN = "driver_count";
}
