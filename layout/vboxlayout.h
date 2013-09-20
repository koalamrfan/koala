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
    virtual int CalculateLimitMinWidth() const override;
    virtual int CalculateLimitMinHeight() const override;
    virtual int CalculateLimitMaxWidth() const override;
    virtual int CalculateLimitMaxHeight() const override;
    virtual int CalculatePreferWidth() const override;
    virtual int CalculatePreferHeight() const override;
    virtual bool IsUnderPrefer() override;
    virtual void DoUnderPrefer() override;
    virtual void DoExceedPrefer() override;
    virtual void AllocHelperToBox() override;
    void AllocSectionByStrechFactor(int alloc_size, int sum_factor);
    
};
} // namespace ui

#endif