#include "ywindow.h"
#include "SkCanvas.h"
#include "texture_pool.h"
#include "event_factory.h"
#include "event_target.h"

namespace ui
{
LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message) {
    case  WM_ERASEBKGND:
        return true;
    case WM_PAINT:
        window->Draw();
        TexturePool::GetInstance()->CanvasToScreen();
        break;
    case WM_SIZE:
        RECT rect;
        GetClientRect(hwnd, &rect);
        window->SetGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
        window->Relayout();
        break;
    default:
        auto event = EventFactory::GetInstance()->CreateEvent(message, wParam, lParam);
        if(event) {
            window->DoEvent(event.get());
        }
    }
    return CallWindowProc(window->oldProc_, hwnd, message, wParam, lParam);
}

Window::Window(HWND hwnd) {
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);
    oldProc_ = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)Proc);
    hwnd_ = hwnd;
    TexturePool::GetInstance()->Init(this);

    RECT rect;
    GetClientRect(hwnd, &rect);
    SetGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}

void Window::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    SkRect rect = {
        SkIntToScalar(0), SkIntToScalar(0),
        SkIntToScalar(Width()), SkIntToScalar(Height())
    };

    Bitmap() ? GetRenderTactics()->Draw(canvas, Bitmap(), rect, paint) :
        canvas->clear(SK_AlphaTRANSPARENT);
}

void Window::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    TexturePool::GetInstance()->ResizeCanvas(width, height);
    Widget::SetGeometry(x, y, width, height);
}

bool Window::DoEvent(Event* event) {
    if(event->Type() == EventType::kMouseEvent) {
        MouseEvent* mouse_event = reinterpret_cast<MouseEvent*>(event);
        EventTarget* target =  HiTest(mouse_event->X(), mouse_event->Y());
        if(target && target != this) {
            target->DoEvent(mouse_event);
        }
    }
    return true;
}

} // namespace ui