#ifndef BUTTON_H_
#define BUTTON_H_

#include "panel.h"
#include <string>

namespace ui
{
class Button : public Panel
{
public:
    void SetNormalTexture(const std::string& normal);
    void SetOverTexture(const std::string& over);
    void SetPressTexture(const std::string& press);
    
    std::string NormalTexture() const {
        return normal_texture_;
    }

    std::string OverTexture() const {
        return over_texture_;
    }

    std::string PressTexture() const {
        return press_texture_;
    }

    virtual void OnDraw(SkCanvas* canvas) override;
    virtual bool DoEvent(Event* event) override;
private:
    std::string normal_texture_;
    std::string over_texture_;
    std::string press_texture_;
};
} // namespace ui

#endif