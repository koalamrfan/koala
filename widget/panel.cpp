#include "panel.h"
#include "SkCanvas.h"
#include "texture_pool.h"
#include "event.h"
#include "mouse_event.h"

namespace ui
{
void Panel::OnDraw(SkCanvas* canvas, const SkRect& clip_rect) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(0), SkIntToScalar(0),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    auto bitmaps = Bitmap();
    !bitmaps.empty() ? GetRenderTactics()->Draw(canvas, bitmaps[0], rect, paint) :
        canvas->clear(SK_AlphaTRANSPARENT);
}

bool Panel::DoEvent(Event* event) {
    if(event->Type() == EventType::kMouseEvent) {
        MouseEvent* mouse_event = (MouseEvent*)event;
        SkDebugf("Button:%d\n", mouse_event->Button());
        SkDebugf("Action:%d\n", mouse_event->Action());
    }
    return true;
}
} // namespace ui