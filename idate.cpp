#include "idate.h"

IDate::IDate()
{
    set_id();
    my_parent = nullptr;
}

IDate::~IDate()
{
    if (my_parent != nullptr)
    {
        delete my_parent;
    }
}

void IDate::set_id()
{
    static long long my_id = 0;
    my_id++;
    id = my_id;
}

void IDate::set_parent(IDate *parent)
{
    my_parent = parent;
}

long long IDate::get_id()
{
    return id;
}
