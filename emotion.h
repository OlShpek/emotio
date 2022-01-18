#ifndef EMOTION_H
#define EMOTION_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QVector>
#include <QString>
#include <QTextEdit>
#include <QObject>
#include <QToolButton>

class Emotion : public QDialog
{
    Q_OBJECT
public:
    Emotion();
    std::vector<std::pair<QString, QString>> get_emotions();
    QString get_text();
    QString middle_color();
signals:
    void close_window();
private slots:
    void change_border();
    void my_res();
    void end();
private:
    void set_layout(QVBoxLayout* ml, QVector<QPushButton*>& v, const QString& s);
    void set_but_style(QVector<QPushButton*>& v, QVector<QString>& colors);
    int count_middle();

    template<typename T>
    QVector<T*> create_som(int num, T& type);

    QHBoxLayout* main_l = new QHBoxLayout(this);
    QVector<QVector<QPushButton *>> day_buts;
    QPushButton* med_but = new QPushButton(this);
    std::vector<QString> prev;
    QTextEdit* txt = new QTextEdit(this);
    QVector<QString> main_colors = {"#199600", "#26E800", "#B3FF18", "#FFB700", "#FF5800"};
};

#endif // EMOTION_H
