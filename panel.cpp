#include "panel.h"
#include "SkCanvas.h"
#include "texture_pool.h"

namespace ui
{
void Panel::OnDraw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setFilterLevel(SkPaint::kMedium_FilterLevel);
    paint.setStyle(SkPaint::kStroke_Style);

    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()), SkIntToScalar(Y()),
        SkIntToScalar(Width()), SkIntToScalar(Height()));

    Bitmap() ? GetRenderTactics()->Draw(Bitmap(), rect, paint) :
        canvas->drawRect(rect, paint);
    Widget::OnDraw(canvas);
}
} // namespace ui