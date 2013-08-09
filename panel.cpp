#include "panel.h"
#include "SkCanvas.h"
#include "texture_pool.h"
#include "event_target.h"
#include "event.h"

namespace ui
{
void Panel::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    paint.setStyle(SkPaint::kFill_Style);
    paint.setColor(SK_ColorRED);
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()), SkIntToScalar(Y()),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    Bitmap() ? GetRenderTactics()->Draw(canvas, Bitmap(), rect, paint) :
        canvas->drawRect(rect, paint);
    Widget::OnDraw(canvas);
}

bool Panel::DoEvent(Event* event) {
    if(event->Type() == EventType::kMouseEvent) {
        MessageBox(NULL, L"Clicked", L"Clicked", MB_OK);
    }
    return true;
}
} // namespace ui