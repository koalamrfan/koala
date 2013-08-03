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
    Window();
    void Init();
    virtual void OnDraw(SkCanvas* canvas) override;
protected:

    friend LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    WNDPROC oldProc_;

};
} // namespace ui

#endif