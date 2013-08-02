#include <QApplication>
#include <QLayout>

#include "box_layout.h"
#include "hboxlayout.h"
#include "ywindow.h"
#include "button.h"
#include "vboxlayout.h"
#include "layout_space.h"

#include <QImage>
#include <QTimer>
#include <QObject>
#include "timer.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ui::Window win;
    
    win.SetGeometry(100, 100, 300, 200);
    
    ui::HBoxLayout hbox;
    win.SetLayout(&hbox);
    
    ui::LayoutSpace space;
    ui::Button btn1,btn2,btn3,btn4;
    
    btn1.SetText("A");
    btn2.SetText("B");
    btn3.SetText("C");
    btn4.SetText("D");
    
    hbox.AddWidget(&btn1);
    hbox.AddSpace(&space);
    hbox.AddWidget(&btn2);
    hbox.SetStrongElastic(&space);
    hbox.SetStrechFactor(&btn1, 0);
    hbox.SetEastSpace(&btn2, 0);
    hbox.SetWestSpace(&btn2, 0);
    
    ui::VBoxLayout vbox;
    hbox.AddLayout(&vbox);
    hbox.SetStrechFactor(&vbox, 0);
    vbox.AddWidget(&btn3);
    vbox.AddWidget(&btn4);
    
    /*ui::Button btn1,btn2,btn3,btn4;
    btn1.SetText("A");
    btn2.SetText("B");
    btn3.SetText("C");
    btn4.SetText("D");
    
    ui::BoxLayout box;
    win.SetLayout(&box);
    box.AddWidget(&btn1);
    box.AddWidget(&btn2);
    box.AddWidget(&btn3);
    box.AddWidget(&btn4);
    box.SetWestSpace(&btn1, 0);
    box.SetEastSpace(&btn2, 0);
    box.SetNorthSpace(&btn3, 0);
    box.SetSouthSpace(&btn4, 0);*/
    //hbox.RemoveLayout(&vbox);
    
    win.Show();
    win.Relayout();
    
    /* Ä£Äâ onsize */
    Timer c(&win, &btn4, &btn1);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(Update()));
    timer->start(200);

    return app.exec();
}