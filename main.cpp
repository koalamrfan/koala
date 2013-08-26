#include "app.h"
#include "panel.h"
#include "button.h"
#include "hboxlayout.h"

void main(uint32_t argc, TCHAR** argv) {
    ui::Window* window = App::GetInstance()->GetMainWindow();
    ui::Panel* panel1 = new ui::Panel;
    ui::Panel* panel2 = new ui::Panel;
    //button1->SetTexture("normal.png", "hover.png", "press.png");
    panel1->SetSource("mario.png");
    panel2->SetSource("mario.png");
    ui::HBoxLayout *hbox = new ui::HBoxLayout;
    window->SetLayout(hbox);

    panel2->SetParent(panel1);
    panel2->SetGeometry(0, 0, 100, 100);

    hbox->AddWidget(panel1);
    hbox->SetAround(panel1, 100, 100, 100, 100);
    window->Relayout();
}