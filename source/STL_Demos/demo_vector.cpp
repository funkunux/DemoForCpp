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

template<class T>
void ShowElmtPtr(const vector<T> &vec)
{
    debug("vector size: %d, capacity: %d\n", vec.size(), vec.capacity());
    int index = 0;
    for(auto elmt = vec.begin(); elmt != vec.end(); index++, elmt++)
    {
        debug("elmt[%d]: %p\n", index, &(*elmt));
    }
}

template<class T>
class FindAdapter
{
public:
    T start;
    bool isInitialAs;
    FindAdapter(T init, bool isInit = true): start(init), isInitialAs(isInit){}
    bool operator() (T elmt)
    {
        return !(isInitialAs ^ (0 == elmt.find(start)));
    }
};

void ShowStrVec(const vector<string>& vec)
{
    debug("vec capacity:%d size:%d\n", vec.capacity(), vec.size());
    for(auto iter = vec.begin(); iter != vec.end(); iter++)
    {
        debug("vec[%p]: %s, cap:%d\n", &(*iter), (*iter).c_str(), (*iter).capacity());
    }
}

class Test
{
public:
    Test(){debug("Construct[%p]! \n", this);}
    ~Test(){debug("Destruct[%p]!\n", this);}
};

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

    vector<char> vecChar(str.begin(), str.end());
    debug("vecChar:");
    for(auto c : vecChar)
    {
        printf("%c", c);
    }
    printf("\n");

    SEPERATOR;

    vecChar.assign(10, '~');
    debug("vecChar:");
    for(auto c : vecChar)
    {
        printf("%c", c);
    }
    printf("\n");

    SEPERATOR;

    ShowElmtPtr(vecChar);

    SEPERATOR;

    /* push_back 会增加一个元素,若该vector空间已满(size == capacity),则会整个vector重新迁移到新的内存空间处,并分配更大的容量capacity,相当于assign */
    vecChar.push_back('b');
    ShowElmtPtr(vecChar);

    SEPERATOR;

    vecChar.pop_back();
    ShowElmtPtr(vecChar);

    SEPERATOR;

    vector<string> fruit;
    fruit.push_back("apple");
    fruit.push_back("banana");
    fruit.push_back("pineapple");
    fruit.push_back("watermelon");
    fruit.push_back("qiwifruit");
    fruit.push_back("pine");
    ShowElmtPtr(fruit);
    
    sort(fruit.begin(), fruit.end());
    ShowStrVec(fruit);

    SEPERATOR;

    auto iter1 = find_if(fruit.begin(), fruit.end(), FindAdapter<string>("p"));
    auto iter2 = find_if(iter1, fruit.end(), FindAdapter<string>("p", false));
    cout << *iter1 << endl;
    cout << *iter2 << endl;
    fruit.erase(iter1, iter2);
    ShowStrVec(fruit);

    SEPERATOR;

    fruit.insert(iter1, "grape");
    fruit.insert(iter1, "mellon");
    ShowStrVec(fruit);

    SEPERATOR;


    fruit.insert(iter1, "durian");
    fruit.insert(iter1, "lemon");
    ShowStrVec(fruit);
    
    SEPERATOR;

    /* vector insert操作: 与push_back一样,当空间满时,会重新申请空间,并增加capacity容量 */
    fruit.insert(iter1, "mango");
    ShowStrVec(fruit);

    SEPERATOR;
     
     /* vector clear操作: 只清空size,但不释放空间,随时可重新存放元素 */
    vector<Test> vecTest(10);
    ShowElmtPtr(vecTest);
    vecTest.clear();
    vecTest.push_back(Test());
    vecTest.push_back(Test());
    ShowElmtPtr(vecTest);

    SEPERATOR;

    /* vector swap操作: 真正释放空间,此时新增元素须重新申请空间存放,且capacity每次成倍增长 */
    vector<Test>().swap(vecTest);
    ShowElmtPtr(vecTest);
    vecTest.push_back(Test());
    ShowElmtPtr(vecTest);
    vecTest.push_back(Test());
    ShowElmtPtr(vecTest);
    vecTest.push_back(Test());
    ShowElmtPtr(vecTest);
    vecTest.push_back(Test());
    ShowElmtPtr(vecTest);
    vecTest.push_back(Test());
    ShowElmtPtr(vecTest);

    SEPERATOR;

    /* string和vector相似,初始capacity为15,当size>=cap时,会重新申请内存 */
    debug("str[%p] c_str[%p] size:%d, cap:%d\n", &str, str.c_str(), str.size(), str.capacity());
    str = "";
    debug("str[%p] c_str[%p] size:%d, cap:%d\n", &str, str.c_str(), str.size(), str.capacity());
    str = "hello world !!!!!";
    debug("str[%p] c_str[%p] size:%d, cap:%d\n", &str, str.c_str(), str.size(), str.capacity());
    
    SEPERATOR;

    return DEMO_SUCC;
}