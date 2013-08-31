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
    return window_->HitTest(x, y);
}

void App::Update( const SkRect& clip_rect ) {
    RECT rect;
    rect.left = SkScalarFloorToInt(clip_rect.fLeft);
    rect.top = SkScalarFloorToInt(clip_rect.fTop);
    rect.right = SkScalarFloorToInt(clip_rect.fRight);
    rect.bottom = SkScalarFloorToInt(clip_rect.fBottom);
    InvalidateRect(window_->GetHwnd(), &rect, FALSE);
}

void App::DoLayout() {
    window_->Dolayout();
}

Window* App::MainWindow() {
    return window_.get();
}
} // namespace ui