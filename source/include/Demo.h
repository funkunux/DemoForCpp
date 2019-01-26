#ifndef __CPP_DEMO_H_AUTHOR_FUNKUNUX__
#define __CPP_DEMO_H_AUTHOR_FUNKUNUX__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

//#define debug(format, args...) printf("[%s:%u] " format, __FUNCTION__, __LINE__, ##args)
#define DEMO_SUCC 0
#define DEMO_FAIL 1
#define SEPERATOR printf("\n--------------------------\n\n")

using namespace std;

void demo_vector();
void demo_template_unit_program();
void demo_boost_function();
void demo_condition();
void demo_noncopyable();
void demo_mysql(void);
void demo_find_odd_num_of_char(void);
void demo_get_os_endian(void);
void demo_whatever();




#endif
