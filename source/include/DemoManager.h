#ifndef __DEMO_MANAGER__H__
#define __DEMO_MANAGER__H__

#include <vector>
#include <string>
#include <string.h>
#include <functional>

#define MAX_BUFF_SIZE 128

class DemoManager
{
    typedef std::function<void()> demoFuncPtr;
    class Demo
    {
    private:
        char * _info;
    public:
        demoFuncPtr pFunc;
        explicit Demo(demoFuncPtr p, const char* name, const char* desc):pFunc(p)
        {
            _info = new char[MAX_BUFF_SIZE];
            snprintf(_info, MAX_BUFF_SIZE, "%-32s: %s", name, desc);
        }
        const char* Info() const
        {
            return _info;
        } 
        Demo(const Demo& d)
        {
            pFunc = d.pFunc;
            _info = new char[MAX_BUFF_SIZE];
            memcpy(_info, d._info, MAX_BUFF_SIZE);
        }
        ~Demo(){delete _info;}
    };
public:
    void RegistDemo(demoFuncPtr p, const char* name, const char* desc)
    {
        _vecDemo.push_back(Demo(p, name, desc));
    }
    void Run(unsigned int index)
    {
        if(index >= _vecDemo.size())
        {
            printf("There is no demo %d!\n", index);
            ShowInfo();
            return;
        }
        ShowInfo(index);
        _vecDemo[index].pFunc();
    }
    void Run()
    {
        for(unsigned int index = 0; index < _vecDemo.size(); index++) 
        {
            printf("\n============================================================\n");
            Run(index);
            printf("============================================================\n\n");
        }
    }
    void ShowInfo() const
    {
        int index = 0;
        printf("\nList of demos:\n");
        for(auto demo : _vecDemo)
        {
            printf("%d. %s\n", index++, demo.Info());
        }
        printf("\n");
    }

    
    ~DemoManager(){_vecDemo.clear();}
private:
    std::vector<Demo> _vecDemo;
    void ShowInfo(unsigned int index) const
    {
        printf("%d. %s\n", index, _vecDemo[index].Info());
        printf("============================================================\n\n");
    }
};

#endif
