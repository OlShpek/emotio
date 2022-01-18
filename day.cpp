#include "day.h"

Day::Day(const std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path, const QString& name)
    :myxml(name), path(path)
{
    my_em->setStyleSheet("background-color: black;");
    but->setStyleSheet("background-color: black;");
    connect(but, SIGNAL(clicked()), my_em, SLOT(show()));
    connect(my_em, SIGNAL(close_window()), this, SLOT(get_info()));
    but->show();
}

Day::~Day()
{
    delete but;
    delete my_em;
}

void Day::view()
{

}

void Day::get_info()
{
    but->setStyleSheet("background-color: " + my_em->middle_color() + ";");
    my_em->hide();

}
