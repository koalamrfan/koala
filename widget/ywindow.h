#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include "widget.h"

class SkCanvas;
namespace ui
{
class Window : public Widget
{
public:
    Window(HWND hwnd);

    HWND GetHwnd() const {
        return hwnd_;
    }
    virtual void OnDraw(SkCanvas* canvas, const SkRect& clip_rect) override;
    virtual bool DoEvent(Event* event) override;
    virtual void SetGeometry(int x, int y, int width, int height) override;

protected:
    friend LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    WNDPROC oldProc_;
    HWND hwnd_;
};
} // namespace ui

#endif