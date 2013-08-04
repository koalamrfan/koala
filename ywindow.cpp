#include "ywindow.h"
#include "SkCanvas.h"
#include "texture_pool.h"

namespace ui
{
LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message) {
    case WM_PAINT:
        window->Draw();
        break;
    case WM_SIZE:
        RECT rect;
        GetClientRect(hwnd, &rect);
        window->SetGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
        break;
    }
    return CallWindowProc(window->oldProc_, hwnd, message, wParam, lParam);
}

Window::Window(HWND hwnd) {
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);
    oldProc_ = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)Proc);
    hwnd_ = hwnd;
    TexturePool::GetInstance()->Init(this);

    
}

void Window::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setColor(SK_ColorBLACK);
    SkRect rect = {
        SkIntToScalar(0), SkIntToScalar(0),
        SkIntToScalar(Width()), SkIntToScalar(Height())
    };
    canvas->drawRect(rect, paint);
}

void Window::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    TexturePool::GetInstance()->ResizeCanvas(width, height);
    Widget::SetGeometry(x, y, width, height);
}
} // namespace ui