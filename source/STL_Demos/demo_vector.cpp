#include "cppDemo.h"
#include <vector>

template<class T>
typename T::value_type sum(const T& container)
{
    typename T::const_iterator iter = container.begin();
    typename T::value_type s = *iter++;
    while(iter != container.end())
    {
        s += *iter++;
    }
    return s;
}

int main()
{
    debug("DEMO: Vector\n");
    SEPERATOR;
    string str = "hello~";
    char cSum = sum<string>(str);
    debug("str:%s\n", str.c_str());
    debug("cSum:%d\n", cSum);
    SEPERATOR;
    vector<string> strVec(3);
    strVec[0] = "hello ";
    strVec[1] = "world";
    strVec[2] = "!";
    string test;
    for(auto subStr : strVec)
    {
        cout << subStr << endl;
    }
    string strSum = sum<vector<string> >(strVec);
    debug("strSum: %s\n", strSum.c_str());
    SEPERATOR;
    return DEMO_SUCC;
}