#include <assert.h>
#include <stdlib.h>
#include "Demo.h"
#include "DemoManager.h"
#include "Logging.h"

void ShowUsage(const char* str, DemoManager dm)
{
    assert(NULL != str);
    printf("Usage: %s [index]\n", str);
    printf("\n[index]: index of demos\n");
    dm.ShowInfo();
}

int str2uint(const char* str)
{
    assert(NULL != str);
    int num = 0;
    
    for(unsigned int index = 0; str[index]; index++)
    {
        if('0' > str[index] || '9' < str[index])
        {
            DEMO_TRACE("Convert str[%s] to uInt failed! index:%d\n", str, index);
            return EOF;
        }
        num = num * 10 + str[index] - '0';
    }
    
    return num;
}

int main(int argc, char** argv)
{
    Logging::level = Logging::DEBUG;
    DemoManager dm;
    dm.RegistDemo(demo_whatever, "demo_whatever", "Whatever...");
    dm.RegistDemo(demo_vector, "demo_vector", "STL API of vector.");
    dm.RegistDemo(demo_template_unit_program, "demo_template_unit_program", "Demo of unit programming.");
    dm.RegistDemo(demo_boost_function, "demo_boost_function", "Demo of closure function by boost API.");
    dm.RegistDemo(demo_condition, "demo_condition", "Demo of condition and mutex.");
    dm.RegistDemo(demo_noncopyable, "demo_noncopyable", "Demo of noncopyable class.");
    dm.RegistDemo(demo_mysql, "demo_mysql", "Demo of mysql.");
    dm.RegistDemo(demo_find_odd_num_of_char, "demo_find_odd_num_of_char", "Simple algorithm to find the odd num of char.");
    dm.RegistDemo(demo_get_os_endian, "demo_get_os_endian", "Demo for get OS endian.");
    dm.RegistDemo(demo_object_pool, "demo_object_pool", "Thread saved object pool.");

    switch(argc)
    {
        case 1:
            dm.Run();
            return 0;
        case 2:
        {
            int index = str2uint(argv[1]);
            if(0 > index) break;
            dm.Run(index);
            return 0;
        }
        default:
            break;
    };
    ShowUsage(argv[0], dm);

    return 0;
}