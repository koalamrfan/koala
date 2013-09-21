#ifndef FREE_STAY_H_
#define FREE_STAY_H_

#include <memory>

namespace ui
{
class LayoutBaseItem;
class FreeStay
{
public:
    static FreeStay* GetInstance();
    void Set(LayoutBaseItem* layout_base_item);
protected:
    FreeStay();
    ~FreeStay();

    LayoutBaseItem* layout_base_item_;
};
} // namespace ui

#endif