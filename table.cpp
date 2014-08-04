#include "table.h"
#include "ui_table.h"


table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    update_screen();
    QObject::connect(QApplication::primaryScreen(), SIGNAL(geometryChanged(QRect)), this, SLOT(update_screen()));
    QTimer *timer = new QTimer();
    timer->start(1000);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateHTTP()));
    this->setStyleSheet( "QPushButton{"
                        "background-color: green;"
                         "border-radius: 5px}"
                    );
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
    CanIUpdateDataFromSQL_QUEUE = 0;
}

void table::update_screen()
{
    h = screenH;    //QApplication::primaryScreen()->size().height();
    w = screenW;    //QApplication::primaryScreen()->size().width();

    ui->verticalLayoutWidget->setGeometry(QRect(0, 0, w, h));
    this->setGeometry(QRect(0, 0, w, h));
}

QString table::getHttp()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager *pManager = new QNetworkAccessManager();
    connect(pManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(QUrl(QString("http://192.168.1.168/data?direction=" + directionID)));
    QNetworkReply *reply = pManager->get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString str("No Signal");
    str = QString(reply->readAll());
    delete pManager;
    return str;
}

//json с костылями. Сначала идет 1, 6, 7, 8, потом 2, 3, 4, 5. экспериментально вывел.
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
    //А вдруг мы ещё не дошли до этого шага,
    //А клиент уже ломится за данными
    if(CanIUpdateDataFromSQL_QUEUE == 1)
        parserJSON(getHttp());
}

void table::replyFinish(QNetworkReply *)
{
}
void table::on_p00_03_clicked()
{  
    timeID = "1";
    standToQueue();
}
void table::on_p03_06_clicked()
{   
    timeID = "2";
    standToQueue();
}
void table::on_p06_09_clicked()
{
    timeID = "3";
    standToQueue();
}
void table::on_p09_12_clicked()
{
    timeID = "4";
    standToQueue();
}
void table::on_p12_15_clicked()
{
    timeID = "5";
    standToQueue();
}
void table::on_p15_18_clicked()
{
    timeID = "6";
    standToQueue();
}
void table::on_p18_21_clicked()
{
    timeID = "7";
    standToQueue();
}
void table::on_p21_24_clicked()
{
    timeID = "8";
    standToQueue();
}

void table::standToQueue()
{
    qDebug() << HUMAN << "=human " << timeID;
    QNetworkAccessManager *pManager = new QNetworkAccessManager();
    connect(pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
    pManager->post(QNetworkRequest(QUrl(QString("http://192.168.1.168/q" + HUMAN + "?"))),
                   QString("id=" + PHONE_NUMBER + "&time=" + timeID + "&seats=" + NUMBER_OF_SEATS).toUtf8());

    delete pManager;
}
