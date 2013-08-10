#include "panel.h"
#include "SkCanvas.h"
#include "texture_pool.h"
#include "event_target.h"
#include "event.h"
#include "mouse_event.h"

namespace ui
{
void Panel::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()), SkIntToScalar(Y()),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    Bitmap() ? GetRenderTactics()->Draw(canvas, Bitmap(), rect, paint) :
        canvas->clear(SK_AlphaTRANSPARENT);
    Widget::OnDraw(canvas);
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