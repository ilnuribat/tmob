#include <QObject>
#include <QApplication>
#include "registration.h"
#include "table.h"
#include "welcome.h"
#include <QDebug>
#include <QScreen>
#include <QString>
#include "extern_variables.h"

extern QString human;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    welcome w;
    w.show();
    registration r;
    table t;
    QObject::connect(&w, SIGNAL(next_button()), &r, SLOT(show()));//welcome -> registration
    QObject::connect(&r, SIGNAL(prev_button()), &w, SLOT(show()));//registration -> welcome
    QObject::connect(&r, SIGNAL(next_button()), &t, SLOT(show()));//registration -> table
    QObject::connect(&t, SIGNAL(prev_button()), &r, SLOT(show()));//table -> registration

    return a.exec();
}
