#include "free_stay.h"

namespace ui
{
FreeStay* FreeStay::GetInstance() {
    static FreeStay free_stay;
    return &free_stay;
}

void FreeStay::Set(LayoutBaseItem* layout_base_item) {
    layout_base_item_ = layout_base_item;
}

FreeStay::FreeStay():layout_base_item_(nullptr) {

}

FreeStay::~FreeStay() {
    if(layout_base_item_) {
        delete layout_base_item_;
        layout_base_item_ = nullptr;
    }
}
} // namespace ui