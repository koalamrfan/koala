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
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()), SkIntToScalar(Y()),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    Bitmap() ? GetRenderTactics()->Draw(canvas, Bitmap(), rect, paint) :
        canvas->clear(SK_AlphaTRANSPARENT);
    Widget::OnDraw(canvas);
}

bool Panel::DoEvent(Event* event) {
    if(event->Type() == EventType::kMouseEvent) {
        MessageBox(NULL, L"Clicked", L"Clicked", MB_OK);
    }
    return true;
}
} // namespace ui