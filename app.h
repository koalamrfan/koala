#ifndef APP_H
#define APP_H

#include <windows.h>
#include "ywindow.h"
#include <memory>

class App
{
public:
    static App* GetInstance();

    void Init(HWND hwnd, uint32_t argc, TCHAR** argv);

    ui::Window* GetMainWindow() const {
        return window_.get();
    }
protected:
    App() {}

private:
   std::shared_ptr<ui::Window> window_; 
};


extern void main(uint32_t argc, TCHAR** argv);
#endif