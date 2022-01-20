#include "mainwindow.h"

#include <QApplication>
#include "day.h"
#include "emotion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*Emotion em;
    em.setStyleSheet("background-color: black;");
    em.show();*/
    Day d({{"calendar", {}}, {"day", {}}}, "calendar.xml");
    d.view();
    d.show();
    return a.exec();
}
