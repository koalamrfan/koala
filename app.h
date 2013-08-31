#ifndef APP_H
#define APP_H

#include <windows.h>
#include "ywindow.h"
#include "widget.h"
#include "SkRect.h"
#include <memory>

namespace ui
{
class App
{
public:
    static void Init(HWND hwnd, uint32_t argc, TCHAR** argv);
    static Widget* MainWindowHitest(int32_t x, int32_t y);
    static void Update(const SkRect& clip_rect);
    static void DoLayout();
    static Window* MainWindow();

private:
   static std::shared_ptr<ui::Window> window_; 
};
} // namespace ui

extern void main(uint32_t argc, TCHAR** argv);
#endif