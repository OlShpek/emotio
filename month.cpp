#include "month.h"

Month::Month()
{

}

Month::~Month()
{
    for (int i = children.size() - 1; i >= 0; i--)
    {
        delete children[i];
    }
}
