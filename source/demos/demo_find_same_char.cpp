#include <iostream>
#include "Logging.h"
#include "Demo.h"

void demo_find_odd_num_of_char(void)
{
    char array[] = "abcaabacd";
    char target = array[0];
    for(int i = 1; array[i]; i++)
    {
        target = ~(target ^ array[i]);
    }
    cout << "target:" << target << endl;
}