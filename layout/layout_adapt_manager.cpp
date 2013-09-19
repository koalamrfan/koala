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

bool LayoutAdaptManager::AdaptOpened() const {
    return adapt_opened_;
}

void LayoutAdaptManager::OpenAdapt() {
    adapt_opened_ = true;
}

void LayoutAdaptManager::CloseAdapt() {
    adapt_opened_ = false;
}

void ui::LayoutAdaptManager::Drive() {
    if(adapt_opened_ == false) {
        return ;
    }
    App::DoLayout();
}
} // namespace ui

