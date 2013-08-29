#include "layout_adapt_manager.h"
#include "app.h"

namespace ui
{
LayoutAdaptManager::LayoutAdaptManager():adapt_opened_(false) {
    
}

LayoutAdaptManager* LayoutAdaptManager::GetInstance() {
    static LayoutAdaptManager layout_adapt_manager;
    return &layout_adapt_manager;
}

void LayoutAdaptManager::Push( LayoutAdaptItem* item) {
    layout_adapt_items_.push_back(item);
}

LayoutAdaptManager::LayoutAdaptItem* LayoutAdaptManager::FindPublicItem() const {
    if(layout_adapt_items_.size() == (uint32_t)1) {
        layout_adapt_items_[0];
    }
    //TODO
    return nullptr;
}

bool LayoutAdaptManager::AdaptOpened() const {
    return adapt_opened_;
}

void LayoutAdaptManager::OpenAdapt() {
    adapt_opened_ = true;
}

void LayoutAdaptManager::CloseAdapt() {
    adapt_opened_ = false;
}

void ui::LayoutAdaptManager::Flush() {
    if(adapt_opened_ == false) {
        return ;
    }
    App::GetInstance()->GetMainWindow()->Dolayout();
    auto iter = layout_adapt_items_.begin();
    while (iter != layout_adapt_items_.end()) {
        (*iter)->Update();
        iter++;
    }
}
} // namespace ui

