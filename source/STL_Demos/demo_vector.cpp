#include "cppDemo.h"
#include <vector>
#include <algorithm>

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

template<class T>
typename T::const_iterator rfind(const T& container, typename T::value_type value)
{
#if 1
    typename T::const_reverse_iterator riter = find(container.rbegin(), container.rend(), value);
#else
    typename T::reverse_iterator riter = container.rbegin();
    for(; riter != container.rend() && *riter != value; riter++);
#endif
    if(riter == container.rend()) return container.end();
    typename T::const_iterator iter = riter.base();
    return --iter;
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
    string strSum = sum(strVec);
    debug("strSum: %s\n", strSum.c_str());
    SEPERATOR;
    auto iter = rfind(strVec, "world");
    if(iter == strVec.end())
        debug("Can't rfind the key!\n");
    else
        debug("rfind the key!\n");
    SEPERATOR;
    return DEMO_SUCC;
}