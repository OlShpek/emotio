#include "day.h"

Day::Day(const std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path, const QString& name)
    :myxml(name), path(path)
{
    my_em->setStyleSheet("background-color: black;");
    but->setStyleSheet("background-color: black;");
    connect(but, SIGNAL(clicked()), my_em, SLOT(show()));
    connect(my_em, SIGNAL(close_window()), this, SLOT(get_info()));
    connect(this, SIGNAL(recov_info(const std::vector<std::pair<QString, QString>>&, const QString&)), my_em, SLOT(get_info(const std::vector<std::pair<QString, QString>>&,  const QString&)));
    but->show();
}

Day::~Day()
{
    delete but;
    delete my_em;
}

void Day::view()
{
    auto nal = myxml.get_all_attr(path);
    for (int i = 0; i < nal.size(); i++)
    {
        if (nal[i].first == "main_color" && nal[i].second != "black")
        {
            but->setStyleSheet("background-color: " + nal[i].second + ';');
            emit recov_info(nal, myxml.get_tag_val(path));
            break;
        }
    }
}

void Day::get_info()
{
    but->setStyleSheet("background-color: " + my_em->middle_color() + ";");
    myxml.redact_attr(path, {{"main_color", my_em->middle_color()}});
    myxml.redact_attr(path, my_em->get_emotions());
    myxml.redact_text(path, my_em->get_text());
    my_em->hide();

}
