#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include "extern_vars.h"

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
    void update_screen();

signals:
    void prev_button();
    void next_button();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:
    Ui::registration *ui;
};

#endif // REGISTRATION_H
