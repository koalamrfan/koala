#include "app.h"
#include "panel.h"
#include "button.h"
#include "hboxlayout.h"

void main(uint32_t argc, TCHAR** argv) {
    ui::Window* window = App::GetInstance()->GetMainWindow();
    ui::Button* button1 = new ui::Button;
    ui::Panel* panel2 = new ui::Panel;
    button1->SetTexture("btn1.png", "btn2.png", "btn3.png");
    panel2->SetSource("mario.png");
    ui::HBoxLayout *hbox = new ui::HBoxLayout;
    window->SetLayout(hbox);
    hbox->AddWidget(button1);
    hbox->SetWestSpace(button1, 0);
    hbox->SetSouthSpace(button1, 0);
    hbox->AddWidget(panel2);
    hbox->SetAround(panel2, 0, 0, 0, 0);
    hbox->SetStrongElastic(panel2);
    window->Relayout();
}