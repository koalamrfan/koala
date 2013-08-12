#include "button.h"
#include "mouse_event.h"

namespace ui
{

Button::Button():state_(ButtonState::kNormal) {

}

void Button::SetTexture(const std::string& normal,
                const std::string& over,
                const std::string& press) {
    std::string source(normal);
    source+=":";
    source+=over;
    source+=":";
    source+=press;
    SetSource(source);
}

void Button::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()), SkIntToScalar(Y()),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    auto bitmaps = Bitmap();
    if(bitmaps.size() == state_num) {
        SkBitmap* bitmap = nullptr;
        switch(state_) {
            case ButtonState::kNormal:
                bitmap = bitmaps[0];
                break;
            case ButtonState::kOver:
                bitmap = bitmaps[1];
                break;
            case ButtonState::kDownd:
                bitmap = bitmaps[2];
                break;
        }
        if(bitmap) {
            GetRenderTactics()->Draw(canvas, bitmap, rect, paint);
        }
    }
}

bool Button::DoEvent(Event* event) {
    if(event->Type() == EventType::kMouseEvent) {
        MouseEvent* mouse_event = (MouseEvent*)event;
        auto pre_state = state_;
        if(mouse_event->Action() == MouseAction::kPress) {
            state_ = ButtonState::kDownd;
        } else if(mouse_event->Action() == MouseAction::kCome) {
            state_ = ButtonState::kOver;
        } else if(mouse_event->Action() == MouseAction::kLeave) {
            state_ = ButtonState::kNormal;
        } else if(mouse_event->Action() == MouseAction::kRelease) {
            state_ = ButtonState::kOver;
        }
        if(pre_state != state_) {
            Update();
        } 
    }
    return true;
}
} // namespace ui