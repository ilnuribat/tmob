#include "registration.h"
#include "ui_registration.h"


registration::registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    qDebug() << "registration: Concstruct";

    NUMBER_OF_SEATS = "1";
    timer = new QTimer;
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_screen));
    towns.push_back("null");
    getCities();
    ui->pushButton->setStyleSheet(
                        "background-color: green;"
                        "border-style: outset;"
                        "border-radius: 15px;"
                        "border-color: beige;"
                        "font: bold 20px;"
                    );
}

void registration::getCities()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager *pManager = new QNetworkAccessManager();
    connect(pManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(QUrl(QString("http://192.168.1.168/towns")));
    QNetworkReply *reply = pManager->get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString str("No Signal");
    str = QString(reply->readAll());
    QStringList cities = str.split('"');
    QString city;
    for(int i = 0; i < cities.size(); i ++)
    {
        city = QString(cities.at(i).toUtf8());
        if(city.size() > 1){
            towns.push_back(city);
            ui->comboBox->addItem(city);
            ui->comboBox_2->addItem(city);
        }
    }
    qDebug() << towns << "towns";
    source = "1";
    destination = "1";
    delete pManager;
}

registration::~registration()
{
    delete ui;
}

void registration::on_pushButton_2_clicked()
{
    this->hide();
    emit prev_button();
}

void registration::on_pushButton_clicked()
{
    //"next" button
    getDirection();
    if(directionID == "0")
    {
        ui->log->setText("Можно ехать либо в Уфу, либо из Уфы");
    } else {
        this->hide();
        emit next_button();
        CanIUpdateDataFromSQL_QUEUE = 1;
    }
}

void registration::getDirection()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager *pManager = new QNetworkAccessManager();
    connect(pManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(QUrl(QString("http://192.168.1.168/direction?source=" + source + "&destination=" + destination)));
    QNetworkReply *reply = pManager->get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString str("No Signal");
    str = QString(reply->readAll());
    directionID = str;
    qDebug() << str << "directionID";
    delete pManager;
}

void registration::update_screen()
{
    h = screenH;    //QApplication::primaryScreen()->size().height();
    w = screenW;    //QApplication::primaryScreen()->size().width();
    ui->gridLayoutWidget->setGeometry(QRect(0, 0, w, h));
    //qDebug() << "reg update screen";
    //qDebug() << ui->gridLayoutWidget->geometry().size();
    //this->setGeometry(QRect(0, 0, w, h));
}

void registration::on_comboBox_activated(const QString &arg1)
{
    for(int i = 0; i < towns.size(); i++)
        if(towns[i] == arg1)
            source = QString::number(i);
}

void registration::on_comboBox_2_activated(const QString &arg1)
{
    for(int i = 0; i < towns.size(); i++)
        if(towns[i] == arg1)
            destination = QString::number(i);
}
