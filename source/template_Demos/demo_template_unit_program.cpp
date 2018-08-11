#include "cppDemo.h"
#include <string.h>
#include "Logging.h"


template<const char* str>
class Info
{
public:
    const char* msg;
    Info():msg(str){}
};

template<int N>
int length(char (&arr)[N])
{
    return N;
}

template<int N, int M>
int sum()
{
    return N + M;
}


char Msg[] = "Demo of translation unit";

int main()
{
    Logging::level = Logging::DEBUG;
    Info<Msg> info;
    DEMO_INFO("Info: %s\n", info.msg);
    DEMO_DEBUG("Length: %d\n", length(Msg));
    DEMO_DEBUG("Sum: %d\n", sum<2, 3>());
    return 0;
}



