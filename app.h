#ifndef APP_H
#define APP_H

#include <windows.h>

class App
{
public:
    static App* GetInstance();

    void Init(HWND hwnd);
    HWND GetHwnd() const {
        return hwnd_;
    }
protected:
    App() {}

private:
    HWND hwnd_;
};

#endif