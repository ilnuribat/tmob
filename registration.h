#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include "extern_vars.h"
#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <QStringList>
#include <QObject>

namespace Ui {
class registration;
}

class registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = 0);
    ~registration();
    int h, w;
    QTimer *timer;
    void getCities();
    void getDirection();
signals:
    void prev_button();
    void next_button();

private slots:
    void on_pushButton_2_clicked();
    void update_screen();
    void on_pushButton_clicked();
    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_2_activated(const QString &arg1);

private:
    Ui::registration *ui;
};

#endif // REGISTRATION_H
