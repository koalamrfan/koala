#ifndef APP_H
#define APP_H

#include <windows.h>

class App
{
public:
    static App* GetInstance();

    void Init(HWND hwnd);
protected:
    App() {}
};

#endif