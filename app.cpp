#include "app.h"
#include "texture_pool.h"

namespace ui
{
std::shared_ptr<Window> App::window_;

void App::Init(HWND hwnd, int argc, TCHAR** argv) {
    window_ = std::make_shared<Window>(hwnd);

    main(argc, argv);
}

Widget* App::MainWindowHitest(int x, int y) {
    if(window_) {
        return window_->HitTest(x, y);
    } else {
        return nullptr;
    }
}

void App::Update( const SkRect& clip_rect ) {
    if(window_) {
        RECT rect;
        rect.left = SkScalarFloorToInt(clip_rect.fLeft);
        rect.top = SkScalarFloorToInt(clip_rect.fTop);
        rect.right = SkScalarFloorToInt(clip_rect.fRight);
        rect.bottom = SkScalarFloorToInt(clip_rect.fBottom);
        InvalidateRect(window_->GetHwnd(), &rect, FALSE);
    }
}

void App::DoLayout() {
    if(window_) {
        window_->Dolayout();
    }
}

Window* App::MainWindow() {
    if(window_) {
        return window_.get();
    } else {
        return nullptr;
    }
}
} // namespace ui