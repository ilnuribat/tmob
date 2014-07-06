#include "table.h"
#include "ui_table.h"
#include <QApplication>
#include <QScreen>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValueRef>
#include <QTimer>
#include <QUrl>
#include <QString>
#include <QDebug>

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    update_screen();
    QObject::connect(QApplication::primaryScreen(), SIGNAL(geometryChanged(QRect)), this, SLOT(update_screen()));
    QTimer *timer = new QTimer();
    timer->start(1000);
    pManager = new QNetworkAccessManager;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateHTTP()));
}

table::~table()
{
    delete ui;
}

void table::on_pushButton_clicked()
{
    this->hide();
    emit prev_button();
    update_screen();
}

void table::update_screen()
{
    h = QApplication::primaryScreen()->availableSize().height();
    w = QApplication::primaryScreen()->availableSize().width();

    ui->verticalLayoutWidget->setGeometry(QRect(0, 0, w, h));
}

QString table::getHttp()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(QUrl(QString("http://194.58.100.50/data")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString str("No Signal");
    str = QString(reply->readAll());
    return str;
}

//json с костылями. Сначала идет 0, 5, 6, 7, потом 1, 2, 3, 4. экспериментально вывел.
void table::parserJSON(QString httpResponse)
{
    QJsonDocument d = QJsonDocument::fromJson(httpResponse.toUtf8());//
        QJsonObject jsonObj = d.object();

        for(QJsonObject::iterator it = jsonObj.begin(); it != jsonObj.end(); it++)
        {
            QJsonValueRef tmp = (it.value());
            QJsonObject CJson = tmp.toObject();
            QJsonObject::iterator cell = CJson.begin();

            if(it == jsonObj.begin()){
                ui->car_00->setNum(cell.value().toDouble());
                cell++;
                ui->human_00->setNum(cell.value().toDouble());
                cell++;
                //ui->success_00->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 5){
                ui->car_03->setNum(cell.value().toDouble());
                cell++;
                ui->human_03->setNum(cell.value().toDouble());
                cell++;
                //ui->success_03->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 6){
                ui->car_06->setNum(cell.value().toDouble());
                cell++;
                ui->human_06->setNum(cell.value().toDouble());
                cell++;
                //ui->success_06->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 7){
                ui->car_09->setNum(cell.value().toDouble());
                cell++;
                ui->human_09->setNum(cell.value().toDouble());
                cell++;
                //ui->success_09->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 1){
                ui->car_12->setNum(cell.value().toDouble());
                cell++;
                ui->human_12->setNum(cell.value().toDouble());
                cell++;
                //ui->success_12->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 2){
                ui->car_15->setNum(cell.value().toDouble());
                cell++;
                ui->human_15->setNum(cell.value().toDouble());
                cell++;
                //ui->success_15->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 3){
                ui->car_18->setNum(cell.value().toDouble());
                cell++;
                ui->human_18->setNum(cell.value().toDouble());
                cell++;
                //ui->success_18->setNum(cell.value().toDouble());
            }
            else if(it == jsonObj.begin() + 4){
                ui->car_21->setNum(cell.value().toDouble());
                cell++;
                ui->human_21->setNum(cell.value().toDouble());
                cell++;
                //ui->success_21->setNum(cell.value().toDouble());
            }
        }
}

void table::updateHTTP()
{
    parserJSON(getHttp());
}

void table::replyFinish(QNetworkReply *)
{
}

void table::on_p00_03_clicked()
{  
    standToQueue("0");
}

void table::on_p03_06_clicked()
{   
    standToQueue("3");
}

void table::on_p06_09_clicked()
{
    standToQueue("6");
}

void table::on_p09_12_clicked()
{
    standToQueue("9");
}

void table::on_p12_15_clicked()
{
    standToQueue("12");
}

void table::on_p15_18_clicked()
{
    standToQueue("15");
}

void table::on_p18_21_clicked()
{
    standToQueue("18");
}

void table::on_p21_24_clicked()
{
    standToQueue("21");
}

void table::standToQueue(QString time)
{
    connect(pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
    pManager->post(QNetworkRequest(QUrl("http://194.58.100.50/post")),
                   QString("method=addingToQueue&source=Ufa&destination=Sibay&time="
                           + time + "&human=" + HUMAN + "&seats=" + NUMBERR_OF_SEATS).toUtf8());
}
