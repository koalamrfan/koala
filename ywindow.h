#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include "widget.h"
#include "app.h"

class SkCanvas;
namespace ui
{
class Window:public Widget
{
public:
    Window(HWND hwnd);

    HWND GetHwnd() const {
        return hwnd_;
    }
    virtual void OnDraw(SkCanvas* canvas) override;
protected:

    friend LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    WNDPROC oldProc_;
    HWND hwnd_;
};
} // namespace ui

#endif