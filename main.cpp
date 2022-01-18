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
    Day d({{"file", {}}, {"name", {{"v", "misha"}}}, {"contact", {{"kpp", "r"}}}}, "31");
    d.show();
    /*MyXml xml(QDir::currentPath() + "calendar.xml");
    auto v = xml.get_all_attr({{"calendar", {}}, {"day", {"color", "black"}}});
    for (int i = 0; i < v.size(); i++)
    {
        qDebug() << v[i].first;
        for (int j = 0; j < v[i].second.size(); j++)
        {
            qDebug() << v[i].second[j];
        }
    }*/
    return a.exec();
}
