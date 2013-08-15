#include "texture.h"
#include "SkCanvas.h"
#include "app.h"
#include <windows.h>

namespace ui
{
Texture::Texture():
    auto_region_active_(true),
    region_mode_(VisualRegionMode::kAuto){

}

void Texture::MakeInnerBitmap() {
    inner_bitmap_ = std::make_shared<SkBitmap>();
    SkRect rect = GetInnerBitmapRect();
    inner_bitmap_->setConfig(SkBitmap::kARGB_8888_Config, SkScalarFloorToInt(rect.width()), SkScalarFloorToInt(rect.height()));
    inner_bitmap_->allocPixels();
    inner_canvas_ = std::make_shared<SkCanvas>(*inner_bitmap_);
    inner_canvas_->clear(SK_AlphaTRANSPARENT);
    inner_canvas_->translate(SkIntToScalar(-rect.x()), SkIntToScalar(-rect.y()));
    OnDraw(inner_canvas_.get());
}
void Texture::Draw(const SkRect& clip_rect) {
    if(!clip_rect.contains(GetInnerBitmapRect())) {
        return ;
    }
    auto canvas = TexturePool::GetInstance()->GetCanvas();
    canvas->save();
    if(auto_region_active_ && region_mode_ == VisualRegionMode::kAuto) {
        MakeInnerBitmap();
        auto_region_active_ = false;
    }
    OnDraw(canvas);
    canvas->restore();
} 

void Texture::Update() {
    RECT rect;
    SkRect sk_rect = GetInnerBitmapRect();
    rect.left = SkScalarFloorToInt(sk_rect.fLeft);
    rect.top = SkScalarFloorToInt(sk_rect.fTop);
    rect.right = SkScalarFloorToInt(sk_rect.fRight);
    rect.bottom = SkScalarFloorToInt(sk_rect.fBottom);
    InvalidateRect(App::GetInstance()->GetMainWindow()->GetHwnd(), &rect, FALSE);
}

void Texture::SetSource(const std::string& source) {
    source_ = source;
}

std::vector<SkBitmap*> Texture::Bitmap() {
    return TexturePool::GetInstance()->CreateBitmapFromSource(source_);
}

void Texture::SetRegionMode(VisualRegionMode region_mode) {
    region_mode_ = region_mode;
}

std::shared_ptr<BmpRenderTactics> Texture::GetRenderTactics() {
    auto extentd = source_.substr(source_.size() - 6);
    std::shared_ptr<BmpRenderTactics> tactics;
    if(extentd == ".9.png") {
        tactics = TexturePool::GetInstance()->CreatePng9Tactics();
    }else {
        tactics = TexturePool::GetInstance()->CreateNormalTactics();
    }
    return tactics;
}

void Texture::UpdateAutoRegion() {
    auto_region_active_ = true;
}

bool Texture::PointInInnerBitmap(int32_t x, int32_t y) {
    return 0 != *(inner_bitmap_->getAddr32(x, y));
}
} // namespace ui