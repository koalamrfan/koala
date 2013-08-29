#include "ywindow.h"
#include "SkCanvas.h"
#include "texture_pool.h"
#include "event_factory.h"
#include "mouse_event.h"
#include "SkRect.h"

namespace ui
{
LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message) {
    case  WM_ERASEBKGND:
        return true;
    case WM_PAINT:
        {
            RECT rect;
            GetUpdateRect(hwnd, &rect, FALSE);
            SkRect clip_rect = SkRect::MakeXYWH(
                SkIntToScalar(rect.left), 
                SkIntToScalar(rect.top), 
                SkIntToScalar(rect.right - rect.left),
                SkIntToScalar(rect.bottom - rect.top));
            window->Draw(clip_rect);
            TexturePool::GetInstance()->CanvasToScreen(clip_rect);
        }
        break;
    case WM_SIZE:
        {
            if(wParam != SIZE_MINIMIZED) {
                RECT rect;
                GetClientRect(hwnd, &rect);
                window->SetGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
                window->Dolayout();
            }
        }
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            if(window->LimitMaxWidth() < (uint32_t)(INT32_MAX - GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYBORDER))) {
                lpMMI->ptMaxTrackSize.x = window->LimitMaxWidth() + GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYBORDER);
            }
            if(window->LimitMaxHeight() < (uint32_t)(INT32_MAX - GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYBORDER))) {
                lpMMI->ptMaxTrackSize.y = window->LimitMaxHeight() + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER);
            }
            RECT inner_rect, window_rect;
            GetClientRect(hwnd, &inner_rect);
            GetWindowRect(hwnd, &window_rect);

            lpMMI->ptMinTrackSize.x = window->LimitMinWidth() + 
                ((window_rect.right - window_rect.left) - (inner_rect.right - inner_rect.left));

            lpMMI->ptMinTrackSize.y = window->LimitMinHeight() +
                ((window_rect.bottom - window_rect.top) - (inner_rect.bottom - inner_rect.top));
        }
    default:
        auto events = EventFactory::GetInstance()->CreateEvent(message, wParam, lParam);
        for (auto event:events) {
            if(event && event->Target()) {
                event->Target()->DoEvent(event.get());
            }
        }
    }
    return CallWindowProc(window->oldProc_, hwnd, message, wParam, lParam);
}

Window::Window(HWND hwnd) {
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);
    oldProc_ = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)Proc);
    hwnd_ = hwnd;
    TexturePool::GetInstance()->Init(this);

    SetHitRegionMode(HitRegionMode::kEntirely);

    RECT rect;
    GetClientRect(hwnd, &rect);
    SetGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}

void Window::OnDraw(SkCanvas* canvas, const SkRect& clip_rect) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    SkRect rect = {
        SkIntToScalar(0), SkIntToScalar(0),
        SkIntToScalar(Width()), SkIntToScalar(Height())
    };

    auto bitmaps = Bitmap();
    !bitmaps.empty() ? GetRenderTactics()->Draw(canvas, bitmaps[0], rect, paint) :
        canvas->clear(SK_AlphaTRANSPARENT);
}

void Window::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    TexturePool::GetInstance()->ResizeCanvas(width, height);
    Widget::SetGeometry(x, y, width, height);
}

bool Window::DoEvent(Event* event) {
    return true;
}
} // namespace ui