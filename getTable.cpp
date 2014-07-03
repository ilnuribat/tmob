#include "getTable.h"
#include "ui_getTable.h"

getTable::getTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::getTable)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    count = 0;
    timer->start(2000);
}

getTable::~getTable()
{
    delete ui;
}

void getTable::on_pushButton_clicked()
{
    this->close();
}

QString getTable::getHttp()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(QUrl(QString("http://localhost:8888/data")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString str("No Signal");
    str = QString(reply->readAll());
    return str;
}
//Чисто парсим JSon файл. Раскидываем по полочкам
void getTable::parser()
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
            ui->success_00->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 1){
            ui->car_03->setNum(cell.value().toDouble());
            cell++;
            ui->human_03->setNum(cell.value().toDouble());
            cell++;
            ui->success_03->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 2){
            ui->car_06->setNum(cell.value().toDouble());
            cell++;
            ui->human_06->setNum(cell.value().toDouble());
            cell++;
            ui->success_06->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 3){
            ui->car_09->setNum(cell.value().toDouble());
            cell++;
            ui->human_09->setNum(cell.value().toDouble());
            cell++;
            ui->success_09->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 4){
            ui->car_12->setNum(cell.value().toDouble());
            cell++;
            ui->human_12->setNum(cell.value().toDouble());
            cell++;
            ui->success_12->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 5){
            ui->car_15->setNum(cell.value().toDouble());
            cell++;
            ui->human_15->setNum(cell.value().toDouble());
            cell++;
            ui->success_15->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 6){
            ui->car_18->setNum(cell.value().toDouble());
            cell++;
            ui->human_18->setNum(cell.value().toDouble());
            cell++;
            ui->success_18->setNum(cell.value().toDouble());
        }
        if(it == jsonObj.begin() + 7){
            ui->car_21->setNum(cell.value().toDouble());
            cell++;
            ui->human_21->setNum(cell.value().toDouble());
            cell++;
            ui->success_21->setNum(cell.value().toDouble());
        }
    }
}

void getTable::update()
{
    count ++;
    httpResponse = getHttp();
    parser();

}

void getTable::on_pushButton_2_clicked()
{
    this->close();
}

void getTable::on_toolButton_clicked()
{

}

void getTable::on_button_00_03_clicked()
{
    QNetworkAccessManager * pManager = new QNetworkAccessManager;
    connect(pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
    pManager->post(QNetworkRequest(QUrl("http://localhost:8888/post")),
                   QString("method=getQuote&text=TEST_TEXT&format=xml").toUtf8());
                    //QString("method=getQuote&text=TEST_TEXT&format=xml").toUtf8());
}

//Костыли
void getTable::on_time_00_03_linkActivated(const QString &link)
{
    QString q = link;
    q = "Ilnur";
}

void getTable::getReplyFinished()
{

}

void getTable::readyReadReply()
{

}

void getTable::replyFinish()
{

}

void getTable::on_centralWidget_destroyed()
{
}
