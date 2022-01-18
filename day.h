#ifndef DAY_H
#define DAY_H

#include "week.h"
#include "emotion.h"
#include "myxml.h"

class Day : public Week
{
    Q_OBJECT
public:
    Day(const std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path, const QString& name);
    virtual void view() override;
    virtual ~Day();
public slots:
    void get_info();
private:
    QPushButton* but = new QPushButton();
    Emotion* my_em = new Emotion();
    MyXml myxml;
    std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>> path;
};

#endif // DAY_H
