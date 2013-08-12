#include "app.h"
#include "panel.h"
#include "hboxlayout.h"

void main(uint32_t argc, TCHAR** argv) {
    ui::Window* window = App::GetInstance()->GetMainWindow();
    ui::Panel* panel1 = new ui::Panel;
    ui::Panel* panel2 = new ui::Panel;
    panel1->SetSource("mac.png");
    panel2->SetSource("mac.png");
    ui::HBoxLayout *hbox = new ui::HBoxLayout;
    window->SetLayout(hbox);
    hbox->AddWidget(panel1);
    hbox->SetWestSpace(panel1, 0);
    hbox->SetSouthSpace(panel1, 0);
    hbox->AddWidget(panel2);
    hbox->SetAround(panel2, 0, 0, 0, 0);
    hbox->SetStrongElastic(panel2);
    window->Relayout();
}