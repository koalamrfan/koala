#ifndef LINEAR_BOX_LAYOUT_H_
#define LINEAR_BOX_LAYOUT_H_

#include "layout.h"
#include "box_layout_item.h"
#include "box_layout.h"

namespace ui
{
class LayoutBaseItem;  
class LinearBoxLayoutItem;  
class LayoutSpace;

class LinearBoxLayout:public BoxLayout
{
protected:  
    struct AllocHelper
    {
        enum AllocStatus{
            kNoAlloc = 0,
            kTempAlloc,
            kAlloc
        };

        AllocHelper():
            section(0),
            status(kNoAlloc),
            box_item(nullptr) {

        }

        int section;
        AllocStatus status;
        LinearBoxLayoutItem* box_item;
    };
public:
    LinearBoxLayout();
    ~LinearBoxLayout();

    void SetStrechFactor(LayoutBaseItem* item, int strech_factor);
    void SetStrongElastic(LayoutBaseItem* item);
    void SetWeakElastic(LayoutBaseItem* item);

    virtual std::shared_ptr<LayoutItem> CreateLayoutItem() const override;
protected:
    virtual void Relayout() override;
    
    virtual bool IsUnderPrefer() = 0;
    virtual void DoUnderPrefer() = 0;
    virtual void DoExceedPrefer() = 0;
    virtual void AllocHelperToBox() = 0;

    void BoxToAllocHelper();
    bool IsStrongWeakAllInNoAlloc();
    void ResetTempAllocToNoAlloc();

    std::vector<AllocHelper> alloc_sections_;
};
} // namespace ui

#endif