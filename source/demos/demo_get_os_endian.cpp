#include <iostream>
#include "Logging.h"
#include "Demo.h"

void demo_get_os_endian(void)
{
    union
    {
        short s;
        char c[sizeof(short)];
    } un;
    un.s = 0x0102;
    if(sizeof(short) == 2)
    {
        cout << "OS_ENDIAN: ";
        if(un.c[0] == 2 && un.c[1] == 1)
        {
            cout << "little-endian" << endl;
        }
        else if(un.c[0] == 1 && un.c[1] == 2)
        {
            cout << "big-endian" << endl;
        }
        else
        {
            printf("unknown, c[0]:%d, c[1]:%d\n", un.c[0], un.c[1]);
        }
    }
    else
    {
        cout << "failed to get os endian: sizeof(short) = " << sizeof(short) << endl;
    }
}