#include <functional>
#include "Demo.h"
#include "Logging.h"

class CFunction
{
private:
    int getTime;
public:
    CFunction() : getTime(0) {}
    static void staticFunc(){DEMO_INFO("static\n");}
    void nonStatic(){DEMO_INFO("non static\n");}
    void operator()()
    {
        DEMO_INFO("getTime: %d\n", ++getTime);
    }
};

void closure(string str1, string str2)
{
    cout << str1 << ' ' << str2 << endl;
}

typedef void (*ptrStatic)();
typedef void (CFunction::*ptrNonStatic)();
void demo_boost_function()
{
    CFunction cfunc;
    ptrStatic f1 = &CFunction::staticFunc;
    ptrNonStatic f2 = &CFunction::nonStatic;

    typedef function<void ()> ptrAllKind;
    ptrAllKind f3 = CFunction::staticFunc;
    ptrAllKind f4 = bind(&CFunction::nonStatic, cfunc);

    typedef function<void(string, string)> ptrClosure;
    ptrClosure f5 = bind(closure, placeholders::_1, placeholders::_2);
    ptrClosure f6 = bind(closure, placeholders::_1, "Demos");
    ptrClosure f7 = bind(closure, "Closure", "Demos");

    auto f8 = bind(closure, "auto", "f8");

    f1();
    (cfunc.*f2)();
    f3();
    f4();
    f5("Hello", "world");
    f6("Hello", "world");
    f7("Hello", "world");
    f8("Hello", "world");
    for(int i = 0; i < 10; i++) cfunc();
}
