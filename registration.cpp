#include "registration.h"
#include "ui_registration.h"
#include <QApplication>
#include <QScreen>

registration::registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    update_screen();
    NUMBERR_OF_SEATS = "1";
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
    this->hide();
    emit next_button();
}

void registration::update_screen()
{
    h = QApplication::primaryScreen()->availableSize().height();
    w = QApplication::primaryScreen()->availableSize().width();
    ui->gridLayoutWidget->setGeometry(QRect(0, 0, w - 30, h - 30));
}

void registration::on_radioButton_clicked()
{
    NUMBERR_OF_SEATS = "1";
}

void registration::on_radioButton_2_clicked()
{
    NUMBERR_OF_SEATS = "2";
}

void registration::on_radioButton_3_clicked()
{
    NUMBERR_OF_SEATS = "3";
}

void registration::on_radioButton_4_clicked()
{
    NUMBERR_OF_SEATS = "4";
}
