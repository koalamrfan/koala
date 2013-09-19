#ifndef BUTTON_H_
#define BUTTON_H_

#include "panel.h"
#include <string>

namespace ui
{
const int state_num = 3;
enum class ButtonState
{
    kNormal,
    kOver,
    kDownd,
};

class Button : public Panel
{
public:
    Button();

    void SetTexture(const std::string& normal,
                    const std::string& over,
                    const std::string& press);
    
    std::string NormalTexture() const {
        return normal_texture_;
    }

    std::string OverTexture() const {
        return over_texture_;
    }

    std::string PressTexture() const {
        return press_texture_;
    }

    virtual void OnDraw(SkCanvas* canvas, const SkRect& clip_rect) override;
    virtual bool DoEvent(Event* event) override;
private:
    std::string normal_texture_;
    std::string over_texture_;
    std::string press_texture_;

    ButtonState state_;
};
} // namespace ui

#endif