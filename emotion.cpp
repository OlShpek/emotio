#include "emotion.h"

Emotion::Emotion()
{
    //QString label_style = "font-family: dubai; font-size: 24pt; color: #FFDFC4; font-style: italic;";
    prev.resize(3);
    QPushButton ex;
    for (int i = 0; i < 3; i++)
    {
        day_buts.push_back(create_som(main_colors.size(), ex));
        for (int j = 0; j < main_colors.size(); j++)
        {
            day_buts[i][j]->setText(QString::number(i) + QString::number(j));
            connect(day_buts[i][j], SIGNAL(clicked()), this, SLOT(change_border()));
            connect(day_buts[i][j], SIGNAL(clicked()), this, SLOT(my_res()));
        }
        set_but_style(day_buts[i], main_colors);
    }
    QVBoxLayout* main_left = new QVBoxLayout(this);
    QVBoxLayout l;
    QVector<QVBoxLayout*> vl = create_som(3, l);
    QVector<QString> questions = {"Как твоё утро?", "Как тебе середина дня?", "Как тебе вечер?"};
    QLabel* medium = new QLabel("Твой день: ", this);
    medium->setStyleSheet("font-family: dubai; font-size: 24pt; color: #FFDFC4; font-style: italic;");
    med_but->setStyleSheet("background-color: black;");
    QHBoxLayout* res_l = new QHBoxLayout(this);
    res_l->addWidget(medium);
    res_l->addWidget(med_but);
    for (int i = 0; i < day_buts.size(); i++)
    {
        set_layout(vl[i], day_buts[i], questions[i]);
        main_left->addLayout(vl[i]);
    }
    main_left->addLayout(res_l);
    main_l->addLayout(main_left);

    QVBoxLayout* main_right = new QVBoxLayout(this);
    QLabel* intr = new QLabel("Что было интерсного?", this);
    intr->setStyleSheet("font-family: dubai; font-size: 20pt; color: #FFDFC4; font-style: italic;");
    main_right->addWidget(intr);
    txt->setStyleSheet("font-family: dubai; font-size: 15pt; color: #FFDFC4;");
    main_right->addWidget(txt);
    QPushButton* ok = new QPushButton("OK", this);
    ok->setStyleSheet("font-family: dubai; font-size: 15pt; background-color: black; text-align: right; center; color: #FFDFC4; width: ");
    connect(ok, SIGNAL(clicked()), this, SLOT(end()));
    //ok->setSizeIncrement(day_buts[0][0]->width(), day_buts[0][0]->height());
    main_right->addWidget(ok);
    main_l->addLayout(main_right);
}


void Emotion::set_layout(QVBoxLayout* ml, QVector<QPushButton *> &v, const QString &s)
{
    QHBoxLayout* but_l = new QHBoxLayout(this);
    but_l->setSpacing(10);
    for (int i = 0; i < v.size(); i++)
    {
        but_l->addWidget(v[i]);
    }
    QLabel* lbl = new QLabel(s, this);
    lbl->setStyleSheet("font-family: dubai; font-size: 24pt; color: #FFDFC4; font-style: italic;");
    ml->addWidget(lbl);
    ml->addLayout(but_l);
}

void Emotion::set_but_style(QVector<QPushButton *> &v, QVector<QString> &colors)
{
    for (int i = 0; i < v.size(); i++)
    {
        v[i]->setStyleSheet("background-color: " + colors[i] + ';' + " color: " + colors[i] + ';');
    }
}

template<typename T>
QVector<T *> Emotion::create_som(int num, T& type)
{
    QVector<T *> buts;
    for (int i = 0; i < num; i++)
    {
        buts.push_back(new T(this));
    }
    return buts;
}


void Emotion::change_border()
{
    QPushButton* but = (QPushButton*)QObject::sender();
    //qDebug() << but->text();
    int fc = but->text()[0].unicode() - '0', sc = but->text()[1].unicode() - '0';
    //qDebug() <<fc  << sc;
    if (!prev[fc].isEmpty())
    {
        int fc1 = (int)prev[fc][0].unicode() - '0', sc1 = (int)prev[fc][1].unicode() - '0';
        //qDebug() << fc1 << sc1;
        day_buts[fc1][sc1]->setStyleSheet("background-color: " + main_colors[sc1] + ';' + " color: " + main_colors[sc1] + ';');
    }
    //qDebug() << fc << sc;
    prev[fc] = but->text();
    //qDebug() << prev[fc];
    day_buts[fc][sc]->setStyleSheet("background-color: " + main_colors[sc] + ';' + " color: " + main_colors[sc] + ';' + "border: solid 2px red;");
}

void Emotion::my_res()
{
    for (int i = 0; i < 3; i++)
    {
        if (prev[i].isEmpty())
        {
            return;
        }
    }
    med_but->setStyleSheet("background-color: " + main_colors[count_middle()] + ';');
}

void Emotion::end()
{
    for (int i = 0; i < 3; i++)
    {
        if (prev[i].isEmpty())
        {
            return;
        }
    }
    emit close_window();
}

std::vector<std::pair<QString, QString>> Emotion::get_emotions()
{
    int mr = prev[0][1].unicode() - '0', lu = prev[1][1].unicode() - '0', ev = prev[2][1].unicode() - '0';
    return {{"morning", main_colors[mr]}, {"lunch", main_colors[lu]}, {"evening", main_colors[ev]}};
}

QString Emotion::get_text()
{
    return txt->toPlainText();
}

QString Emotion::middle_color()
{
    return main_colors[count_middle()];
}

int Emotion::count_middle()
{
    int val = (prev[0][1].unicode() - '0' + prev[1][1].unicode() - '0' + prev[2][1].unicode() - '0');
    if (val % 3 == 2)
    {
        val++;
    }
    val /= 3;
    return val;
}

void Emotion::get_info(const std::vector<std::pair<QString, QString>>& info, const QString& text)
{
    txt->setText(text);
    for (int i = 0; i < day_buts.size(); i++)
    {
        set_but_style(day_buts[i], main_colors);
    }
    for (int i = 0; i < info.size(); i++)
    {
        if (info[i].first == "main_color")
        {
            med_but->setStyleSheet("background-color: " + info[i].second + ';');
        }
        for (int j = 0; j < main_colors.size(); j++)
        {
            if (info[i].second == main_colors[j])
            {
                QString st = "background-color: " + main_colors[j] +"; color: " + main_colors[j] + ';' + "border: solid 2px;";
                if (info[i].first == "morning")
                {
                    day_buts[0][j]->setStyleSheet(st);
                    prev[0] = day_buts[0][j]->text();
                }
                else if (info[i].first == "lunch")
                {
                    day_buts[1][j]->setStyleSheet(st);
                    prev[1] = day_buts[1][j]->text();
                }
                else if (info[i].first == "evening")
                {
                    day_buts[2][j]->setStyleSheet(st);
                    prev[2] = day_buts[2][j]->text();
                }
            }
        }
    }
}
