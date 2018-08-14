#include <boost/noncopyable.hpp>
#include "Logging.h"

class MyClass : public boost::noncopyable
{
public:
    MyClass()
    {
        DEMO_DEBUG("Constructor: %p\n", this);
    }
    ~MyClass()
    {
        DEMO_DEBUG("Destructor: %p\n", this);
    }
};

void demo_noncopyable()
{
    MyClass mc1;
    MyClass mc2;
    //MyClass mc3(mc1); //error
    //mc2 = mc1;  //error
}