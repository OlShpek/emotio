#ifndef MONTH_H
#define MONTH_H

#include "year_class.h"

class Month : public Year_class
{
public:
    Month();
    virtual ~Month();
private:
    std::vector<IDate*> children;
};

#endif // MONTH_H
