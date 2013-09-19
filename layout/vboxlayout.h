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
    virtual int CalculateLimitMinWidth() override;
    virtual int CalculateLimitMinHeight() override;
    virtual int CalculateLimitMaxWidth() override;
    virtual int CalculateLimitMaxHeight() override;
    virtual int CalculatePreferWidth() override;
    virtual int CalculatePreferHeight() override;
    virtual bool IsUnderPrefer() override;
    virtual void DoUnderPrefer() override;
    virtual void DoExceedPrefer() override;
    virtual void AllocHelperToBox() override;
    void AllocSectionByStrechFactor(int alloc_size, int sum_factor);
    
};
} // namespace ui

#endif