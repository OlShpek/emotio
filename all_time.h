#ifndef ALL_TIME_H
#define ALL_TIME_H

#include "idate.h"
#include <QString>
#include <vector>

class All_time : public IDate
{
public:
    All_time();
    virtual void add(IDate* el) override;
    virtual void remove(long long id) override;
    virtual void view() override;
    virtual ~All_time();
private:
   std::vector<IDate*> children;
};

#endif // ALL_TIME_H
