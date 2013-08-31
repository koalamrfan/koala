#include "app.h"
#include "texture_pool.h"

namespace ui
{
std::shared_ptr<Window> App::window_;

void App::Init(HWND hwnd, uint32_t argc, TCHAR** argv) {
    window_ = std::make_shared<Window>(hwnd);

    main(argc, argv);
}

Widget* App::MainWindowHitest(int32_t x, int32_t y) {
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