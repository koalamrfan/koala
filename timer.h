#ifndef TIMER_H_
#define TIEMR_H_

#include "widget.h"
#include <QObject>

class Timer: public QObject
{
    Q_OBJECT
public:
    Timer(ui::Widget* widget, ui::Widget* awidget, ui::Widget* bwidget) {
        widget_ = widget;
        awidget_ = awidget;
        bwidget_ = bwidget;
        i = 0;
    }

public slots:
    void Update() {
        awidget_->IsVisible() ? awidget_->Hide():awidget_->Show();
        bwidget_->SetPreferWidth(i%600);
        i+=10;
        //widget_->Show();
        //widget_->Relayout();
    }
    
private:
    ui::Widget *widget_;
    ui::Widget *awidget_;
    ui::Widget *bwidget_;
    uint i;
};

#endif
