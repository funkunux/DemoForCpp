#ifndef __CPP_DEMO_H_AUTHOR_FUNKUNUX__
#define __CPP_DEMO_H_AUTHOR_FUNKUNUX__


#include <stdio.h>
#include <iostream>

#define debug(format, args...) printf("[%s:%u] " format, __FUNCTION__, __LINE__, ##args)
#define DEMO_SUCC 0
#define DEMO_FAIL 1
#define SEPERATOR printf("\n--------------------------\n\n")

using namespace std;


#endif