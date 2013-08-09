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


void Texture::Draw() {
    auto canvas = TexturePool::GetInstance()->GetCanvas();
    canvas->save();
    if(auto_region_active_) {
        inner_bitmap_ = std::make_shared<SkBitmap>();
        inner_bitmap_->setConfig(SkBitmap::kARGB_8888_Config, GetInnerBitmapWidth(), GetInnerBitmapHeight());
        inner_bitmap_->allocPixels();
        inner_canvas_ = std::make_shared<SkCanvas>(*inner_bitmap_);
        inner_canvas_->clear(SK_AlphaTRANSPARENT);
        OnDraw(inner_canvas_.get());
        auto_region_active_ = false;
    }
    OnDraw(canvas);
    canvas->restore();
} 

void Texture::SetSource(const std::string& source) {
    source_ = source;
}

SkBitmap* Texture::Bitmap() {
    return TexturePool::GetInstance()->CreateBitmapFromSource(source_);
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
    Draw();
}

bool Texture::PointInInnerBitmap(int32_t x, int32_t y) {
    return 0 != *(inner_bitmap_->getAddr32(x, y));
}
} // namespace ui