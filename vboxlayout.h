#ifndef VBOXLAYOUT_H_
#define VBOXLAYOUT_H_

#include "linear_box_layout.h"

namespace ui
{
class VBoxLayout:public LinearBoxLayout
{
public:
    VBoxLayout();

protected:
    virtual uint32_t CalculateLimitMinWidth() override;
    virtual uint32_t CalculateLimitMinHeight() override;
    virtual uint32_t CalculateLimitMaxWidth() override;
    virtual uint32_t CalculateLimitMaxHeight() override;
    virtual uint32_t CalculatePreferWidth() override;
    virtual uint32_t CalculatePreferHeight() override;
    virtual bool IsUnderPrefer() override;
    virtual void DoUnderPrefer() override;
    virtual void DoExceedPrefer() override;
    virtual void AllocHelperToBox() override;
    void AllocSectionByStrechFactor(uint32_t alloc_size, uint32_t sum_factor);
    
};
} // namespace ui

#endif