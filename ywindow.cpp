#include "ywindow.h"
#include "SkCanvas.h"

namespace ui
{
LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message) {
    case WM_PAINT:
        window->Draw();
        break;
    }
    return CallWindowProc(window->oldProc_, hwnd, message, wParam, lParam);
}

Window::Window() {
    
}

void Window::Init() {
    SetWindowLong(App::GetInstance()->GetHwnd(), GWL_USERDATA, (LONG)this);
    oldProc_ = (WNDPROC)SetWindowLong(App::GetInstance()->GetHwnd(), GWL_WNDPROC, (LONG)Proc);
}

void Window::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    SkRect rect = {
        SkIntToScalar(10), SkIntToScalar(10),
        SkIntToScalar(128), SkIntToScalar(128)
    };
    canvas->drawRect(rect, paint);
}
} // namespace ui