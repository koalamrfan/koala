#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include "widget.h"
#include "app.h"

namespace ui
{
class SkCanvas;
class Window:public Widget
{
public:
    Window();

    virtual void OnDraw(SkCanvas* canvas);
protected:
    friend LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    WNDPROC oldProc_;

};
} // namespace ui

#endif