#include "welcome.h"
#include "ui_welcome.h"


welcome::welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    qDebug() << "constructor";
    update_screen();
    ui->pushButton->setStyleSheet(
                        "background-color: green;"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 15px;"
                        "border-color: beige;"
                        "font: bold 24px;"
                        "padding: 6px;"
                    );
}

welcome::~welcome()
{
    delete ui;
}

void welcome::registrationInServer(QString postData)
{
    QNetworkAccessManager *pManager = new QNetworkAccessManager();
    connect(pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
    pManager->post(QNetworkRequest(QUrl("http://192.168.1.168/registration?")), postData.toUtf8());
}

void welcome::on_pushButton_clicked()
{
    qDebug() << "next button clicked";

    if(HUMAN == "unDefined") return;

    PHONE_NUMBER = ui->phoneNumber->text();
    NAME = ui->lineEdit->text();
    //registrationInServer(QString("human=" + HUMAN + "&name=" + NAME + "&phone=" + PHONE_NUMBER));
    emit next_button();
    this->hide();
}

void welcome::update_screen()
{
    h = screenH;    //QApplication::primaryScreen()->size().height();
    w = screenW;    //QApplication::primaryScreen()->size().width();
    ui->gridLayoutWidget->setGeometry(QRect(0, 0, w, h));
    //this->setGeometry(QRect(0, 0, w, h));
}

void welcome::replyFinish(QNetworkReply *reply)
{
    qDebug() << QString(reply->readAll());
}

void welcome::on_phoneNumber_editingFinished()
{
    ui->phoneNumber->deselect();
}

void welcome::on_pushButton_2_clicked()
{
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
    HUMAN = "driver";
}

void welcome::on_pushButton_3_clicked()
{
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_2->setDisabled(false);
    HUMAN = "passanger";
}
