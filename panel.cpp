#include "panel.h"
#include "SkCanvas.h"

namespace ui
{
void Panel::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setColor(SK_ColorWHITE);
    paint.setStrokeWidth(10);
    paint.setStyle(SkPaint::kStroke_Style);
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()), SkIntToScalar(Y()),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    canvas->drawRect(rect, paint);

    Widget::OnDraw(canvas);
}
} // namespace ui