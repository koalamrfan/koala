#include "app.h"
#include "panel.h"
#include "hboxlayout.h"

void main(uint32_t argc, TCHAR** argv) {
    ui::Window* window = App::GetInstance()->GetMainWindow();
    ui::Panel* panel1 = new ui::Panel;
    //ui::Panel* panel2 = new ui::Panel;
    panel1->SetSource("C:\\Users\\fanfei\\Desktop\\mac.9.png");
    //panel2->SetSource("C:\\Users\\fanfei\\Desktop\\mac.9.png");
    ui::HBoxLayout *hbox = new ui::HBoxLayout;
    window->SetLayout(hbox);
    hbox->AddWidget(panel1);
    hbox->SetAround(panel1, 0, 0, 0, 0);
    
    //hbox->SetWestSpace(panel1, 0);
    //hbox->SetSouthSpace(panel1, 0);
    //hbox->AddWidget(panel2);
    //hbox->SetAround(panel2, 0, 0, 0, 0);
    //hbox->SetStrongElastic(panel2);
    window->Relayout();
}