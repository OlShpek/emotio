#include "all_time.h"

All_time::All_time()
{

}

void All_time::add(IDate* el)
{
    el->set_parent(this);
    children.push_back(el);
}

void All_time::remove(long long id)
{
    for (auto el = children.begin(); el != children.end(); el++)
    {
        if ((*el)->get_id() == id)
        {
            children.erase(el);
            break;
        }
    }
}

void All_time::view()
{

}

All_time::~All_time()
{
    for (int i = children.size() - 1; i >= 0; i--)
    {
        delete children[i];
    }
}
