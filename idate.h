#ifndef IDATE_H
#define IDATE_H

#include <QWidget>
#include <QPushButton>
class IDate : public QWidget
{
public:
    IDate();
    virtual void view() = 0;
    virtual void add(IDate* el) = 0;
    virtual void remove(long long id) = 0;
    virtual ~IDate();
    void set_parent(IDate* parent);
    long long get_id();
protected:
    void set_id();
    IDate* my_parent;
private:
    long long id;
};

#endif // IDATE_H
