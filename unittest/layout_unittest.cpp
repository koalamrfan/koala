#include "gtest/gtest.h"
#include "layout_base_item.h"
#include "layout.h"
#include "layout_item.h"
#include "widget.h"
#include "box_layout_item.h"
#include "box_layout.h"
#include "hboxlayout.h"
#include "vboxlayout.h"

namespace ui
{

namespace
{
class TestWidget : public Widget
{
public:
    virtual void OnDraw(SkCanvas* canvas, const SkRect& clip_rect) {}
};

class TestLayout : public Layout
{
public:
    virtual std::shared_ptr<LayoutItem> CreateLayoutItem() const {
        return std::make_shared<LayoutItem>();
    }

    virtual void Relayout() {}

    virtual int CalculateLimitMinWidth() const override {return 10;}
    virtual int CalculateLimitMinHeight() const override {return 10;}
    virtual int CalculateLimitMaxWidth() const override {return 100;}
    virtual int CalculateLimitMaxHeight() const override {return 100;}
    virtual int CalculatePreferWidth() const override {return 50;}
    virtual int CalculatePreferHeight() const override {return 50;}

    void Expect() {
        TestWidget* w1 = new TestWidget;
        TestWidget* w2 = new TestWidget;
        TestWidget* w3 = new TestWidget;
        EXPECT_TRUE(IsEmpty());
        EXPECT_EQ(Count(), 0);
        auto layoutitem = std::make_shared<LayoutItem>();
        layoutitem->Init(w1);
        AddItem(layoutitem);
        EXPECT_FALSE(IsEmpty());
        EXPECT_EQ(Count(), 1);
        layoutitem = std::make_shared<LayoutItem>();
        layoutitem->Init(w2);
        AddItem(layoutitem);
        EXPECT_EQ(Count(), 2);
        layoutitem = std::make_shared<LayoutItem>();
        layoutitem->Init(w3);
        InsertItem(0, layoutitem);
        EXPECT_EQ(Count(), 3);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), w3);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), w1);
        EXPECT_EQ(ItemAt(2)->GetLayoutBaseItem(), w2);
        RemoveItem(w3);
        EXPECT_EQ(Count(), 2);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), w1);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), w2);
        layoutitem = std::make_shared<LayoutItem>();
        w3 = new TestWidget;
        layoutitem->Init(w3);
        EXPECT_TRUE(InsertItem(2, layoutitem));
        EXPECT_FALSE(InsertItem(2, layoutitem));
        EXPECT_EQ(Count(), 3);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), w1);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), w2);
        EXPECT_EQ(ItemAt(2)->GetLayoutBaseItem(), w3);
        RemoveItem(w3);
        EXPECT_EQ(Count(), 2);
        layoutitem = std::make_shared<LayoutItem>();
        w3 = new TestWidget;
        layoutitem->Init(w3);
        EXPECT_FALSE(InsertItem(3, layoutitem));
        EXPECT_EQ(Count(), 2);
        EXPECT_TRUE(InsertItem(-1, layoutitem));
        EXPECT_EQ(Count(), 3);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), w1);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), w2);
        EXPECT_EQ(ItemAt(2)->GetLayoutBaseItem(), w3);
        EXPECT_TRUE(FindItem(w3) != nullptr);
        RemoveItem(w1);
        RemoveItem(w2);
        RemoveItem(w3);
        EXPECT_FALSE(FindItem(w3) != nullptr);
        EXPECT_TRUE(IsEmpty());
        EXPECT_EQ(Count(), 0);
        EXPECT_FALSE(InsertItem(0, nullptr));
        EXPECT_FALSE(RemoveItem(w3));
        EXPECT_FALSE(RemoveItem(nullptr));
    }
};
} // namespace

TEST(Layout, Layout)
{
    TestLayout test_layout;
    test_layout.AdjustSizes();
    EXPECT_EQ(test_layout.LimitMinWidth(), 10);
    EXPECT_EQ(test_layout.LimitMinHeight(), 10);
    EXPECT_EQ(test_layout.LimitMaxWidth(), 100);
    EXPECT_EQ(test_layout.LimitMaxHeight(), 100);
    EXPECT_EQ(test_layout.PreferWidth(), 50);
    EXPECT_EQ(test_layout.PreferHeight(), 50);
    test_layout.SetPreferWidth(100);
    test_layout.SetPreferHeight(100);
    test_layout.AdjustSizes();
    EXPECT_EQ(test_layout.PreferWidth(), 50);
    EXPECT_EQ(test_layout.PreferHeight(), 50);
    test_layout.Expect();
}

TEST(Layout, BoxLayoutItem)
{
    // basic
    TestWidget* w1 = new TestWidget;
    BoxLayoutItem box_item;
    box_item.Init(w1);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 50);
    EXPECT_EQ(w1->Y(), 50);
    EXPECT_EQ(w1->Width(), 0);
    EXPECT_EQ(w1->Height(), 0);
    w1->SetPreferWidth(50);
    w1->SetPreferHeight(50);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 25);
    EXPECT_EQ(w1->Y(), 25);
    EXPECT_EQ(w1->Width(), 50);
    EXPECT_EQ(w1->Height(), 50);
    box_item.SetAround(0, 0, 0, 0);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kWestValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 50);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 50);
    EXPECT_EQ(w1->Height(), 100);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kNorthValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 50);
    EXPECT_EQ(w1->Y(), 50);
    EXPECT_EQ(w1->Width(), 50);
    EXPECT_EQ(w1->Height(), 50);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kSouthValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 50);
    EXPECT_EQ(w1->Y(), 25);
    EXPECT_EQ(w1->Width(), 50);
    EXPECT_EQ(w1->Height(), 50);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kEastValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 25);
    EXPECT_EQ(w1->Y(), 25);
    EXPECT_EQ(w1->Width(), 50);
    EXPECT_EQ(w1->Height(), 50);
    
    //  set around == set west ..
    box_item.SetAround(10, 10, 50, 50);
    int north_space = box_item.NorthSpace();
    int south_space = box_item.SouthSpace();
    int west_space = box_item.WestSpace();
    int east_space = box_item.EastSpace();
    EXPECT_EQ(north_space, 10);
    EXPECT_EQ(south_space, 50);
    EXPECT_EQ(west_space, 10);
    EXPECT_EQ(east_space, 50);

    box_item.SetAround(0, 0, 0, 0);
    box_item.SetWestSpace(10);
    box_item.SetNorthSpace(10);
    box_item.SetEastSpace(50);
    box_item.SetSouthSpace(50);

    EXPECT_EQ(north_space, 10);
    EXPECT_EQ(south_space, 50);
    EXPECT_EQ(west_space, 10);
    EXPECT_EQ(east_space, 50);

    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(w1->X(), 10);
    EXPECT_EQ(w1->Y(), 10);
    EXPECT_EQ(w1->Width(), 40);
    EXPECT_EQ(w1->Height(), 40);
    
    //  move
    box_item.CalculatePosition(10, 10, 100, 100);
    EXPECT_EQ(w1->X(), 20);
    EXPECT_EQ(w1->Y(), 20);
    EXPECT_EQ(w1->Width(), 40);
    EXPECT_EQ(w1->Height(), 40);

    box_item.CalculatePosition(-10, -10, 100, 100);
    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 40);
    EXPECT_EQ(w1->Height(), 40);

    //west + east > width
    box_item.SetWestSpace(100);
    box_item.CalculatePosition(10, 10, 100, 100);
    EXPECT_EQ(w1->Width(), 0);
    EXPECT_EQ(w1->Height(), 40);

    //north + south > height
    box_item.SetNorthSpace(100);
    box_item.CalculatePosition(10, 10, 100, 100);
    EXPECT_EQ(w1->Width(), 0);
    EXPECT_EQ(w1->Height(), 0);

    // prefer size with limit
    box_item.SetAround(0, 0, 0, 0);
    w1->SetPreferWidth(100);
    w1->SetLimitMaxWidth(50);
    EXPECT_EQ(box_item.PreferWidth(), 50);
    w1->SetLimitMaxWidth(MAX_LENGTH);
    w1->SetLimitMinWidth(200);
    EXPECT_EQ(box_item.PreferWidth(), 200);

    // prefer size with space
    box_item.SetAround(0, 0, 0, 0);
    w1->SetLimitMinWidth(0);
    w1->SetPreferWidth(100);
    w1->SetLimitMaxWidth(MAX_LENGTH);
    box_item.SetWestSpace(10);
    EXPECT_EQ(box_item.PreferWidth(), 110);
    box_item.SetEastSpace(10);
    EXPECT_EQ(box_item.PreferWidth(), 120);

    w1->SetLimitMinHeight(0);
    w1->SetPreferHeight(100);
    w1->SetLimitMaxHeight(MAX_LENGTH);
    box_item.SetNorthSpace(10);
    EXPECT_EQ(box_item.PreferHeight(), 110);
    box_item.SetSouthSpace(10);
    EXPECT_EQ(box_item.PreferHeight(), 120);
    
    // limit size
    box_item.SetAround(0, 0, 0, 0);
    w1->SetLimitMinWidth(100);
    w1->SetPreferWidth(500);
    w1->SetLimitMaxWidth(200);
    EXPECT_EQ(box_item.LimitMinWidth(), 100);
    EXPECT_EQ(box_item.LimitMaxWidth(), 200);

    w1->SetLimitMinHeight(100);
    w1->SetPreferHeight(500);
    w1->SetLimitMaxHeight(200);
    EXPECT_EQ(box_item.LimitMinHeight(), 100);
    EXPECT_EQ(box_item.LimitMaxHeight(), 200);

    // limit size with space
    box_item.SetAround(10, 20, 10, 20);
    EXPECT_EQ(box_item.LimitMinWidth(), 120);
    EXPECT_EQ(box_item.LimitMaxWidth(), 220);
    EXPECT_EQ(box_item.LimitMinHeight(), 140);
    EXPECT_EQ(box_item.LimitMaxHeight(), 240);

    // empty
    TestWidget* w2 = new TestWidget;
    w2->SetLimitMinWidth(50);
    w2->SetLimitMaxWidth(100);
    BoxLayoutItem box_item2;
    box_item2.Init(w2);    

    EXPECT_FALSE(box_item2.IsEmpty());
    w2->Hide();
    EXPECT_TRUE(box_item2.IsEmpty());

    EXPECT_EQ(box_item2.LimitMinWidth(), 0);
    EXPECT_EQ(box_item2.LimitMaxWidth(), MAX_LENGTH);

    w2->Show();
    EXPECT_FALSE(box_item2.IsEmpty());
    
    BoxLayout* layout = new BoxLayout;
    BoxLayoutItem box_item3;
    box_item3.Init(layout);
    EXPECT_TRUE(box_item3.IsEmpty());
    TestWidget* w3= new TestWidget;
    layout->AddWidget(w3);
    EXPECT_FALSE(box_item3.IsEmpty());
}

TEST(Layout, BoxLayout)
{
    // more items
    BoxLayout box_layout;
    box_layout.SetGeometry(0, 0, 200, 200);
    TestWidget* w1 = new TestWidget;
    TestWidget* w2 = new TestWidget;
    TestWidget* w3 = new TestWidget;
    w1->SetPreferWidth(50);
    w1->SetPreferHeight(50);
    w2->SetPreferWidth(100);
    w2->SetPreferHeight(100);

    box_layout.AddWidget(w1);
    box_layout.AddWidget(w2);
    box_layout.AddWidget(w3);

    EXPECT_EQ(box_layout.Count(), 3);

    box_layout.RemoveWidget(w3);

    EXPECT_EQ(box_layout.Count(), 2);

    box_layout.Dolayout();

    EXPECT_EQ(w1->X(), 75);
    EXPECT_EQ(w1->Y(), 75);
    EXPECT_EQ(w1->Width(), 50);
    EXPECT_EQ(w1->Height(), 50);
    
    EXPECT_EQ(w2->X(), 50);
    EXPECT_EQ(w2->Y(), 50);
    EXPECT_EQ(w2->Width(), 100);
    EXPECT_EQ(w2->Height(), 100);


    // prefer width > width
    w1->SetPreferWidth(500);

    box_layout.Dolayout();

    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Width(), 200);

    // prefer width > width
    w1->SetPreferHeight(500);

    box_layout.Dolayout();

    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Height(), 200);

    // inner layout
    BoxLayout* inner_box_layout = new BoxLayout;
    
    w3 = new TestWidget;
    inner_box_layout->AddWidget(w3);
    w3->SetPreferWidth(50);
    w3->SetPreferHeight(50);

    box_layout.AddLayout(inner_box_layout);

    box_layout.Dolayout();

    EXPECT_EQ(w3->X(), 75);
    EXPECT_EQ(w3->Y(), 75);
    EXPECT_EQ(w3->Width(), 50);
    EXPECT_EQ(w3->Height(), 50);
}

TEST(Layout, HBoxLayout)
{
    HBoxLayout hbox_layout;
    hbox_layout.SetGeometry(0, 0, 500, 500);
    TestWidget* w1 = new TestWidget;
    TestWidget* w2 = new TestWidget;
    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(200);
    hbox_layout.AddWidget(w1);
    hbox_layout.AddWidget(w2);

    hbox_layout.Dolayout();
    // default factor is 1
    // alloc width > prefer width
    EXPECT_EQ(w1->X(), 75);
    EXPECT_EQ(w1->Y(), 200);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 275);
    EXPECT_EQ(w2->Y(), 150);
    EXPECT_EQ(w2->Width(), 200);
    EXPECT_EQ(w2->Height(), 200);

    // alloc width < prefer width
    w2->SetPreferWidth(300);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 50);
    EXPECT_EQ(w1->Y(), 200);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 200);
    EXPECT_EQ(w2->Y(), 150);
    EXPECT_EQ(w2->Width(), 300);
    EXPECT_EQ(w2->Height(), 200);

    // alloc height < prefer height
    w2->SetPreferHeight(600);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 50);
    EXPECT_EQ(w1->Y(), 200);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 200);
    EXPECT_EQ(w2->Y(), 0);
    EXPECT_EQ(w2->Width(), 300);
    EXPECT_EQ(w2->Height(), 500);

    hbox_layout.SetStrechFactor(w1, 0);

    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(100);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 200);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 200);
    EXPECT_EQ(w2->Y(), 200);
    EXPECT_EQ(w2->Width(), 200);
    EXPECT_EQ(w2->Height(), 100);

    // factor > 1
    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(100);

    hbox_layout.SetAround(w1, 0, 0, 0, 0);
    hbox_layout.SetAround(w2, 0, 0, 0, 0);

    hbox_layout.SetStrechFactor(w1, 2);
    hbox_layout.SetStrechFactor(w2, 3);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 200);
    EXPECT_EQ(w1->Height(), 500);

    EXPECT_EQ(w2->X(), 200);
    EXPECT_EQ(w2->Y(), 0);
    EXPECT_EQ(w2->Width(), 300);
    EXPECT_EQ(w2->Height(), 500);

    // limit min width
    hbox_layout.SetStrechFactor(w1, 1);
    hbox_layout.SetStrechFactor(w2, 1);

    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(100);

    w1->SetLimitMinWidth(500);

    hbox_layout.SetAroundInValid(w1);
    hbox_layout.SetAroundInValid(w2);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 200);
    EXPECT_EQ(w1->Width(), 500);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->Width(), 0);

    // limit min height
    w1->SetLimitMinHeight(300);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 100);
    EXPECT_EQ(w1->Width(), 500);
    EXPECT_EQ(w1->Height(), 300);

    EXPECT_EQ(w2->Width(), 0);

    // limit max width
    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(100);

    w1->SetLimitMinWidth(0);
    w1->SetLimitMaxWidth(1);

    hbox_layout.SetStrechFactor(w1, 1);
    hbox_layout.SetStrechFactor(w2, 1);

    hbox_layout.SetAround(w1, 0, 0, 0, 0);
    hbox_layout.SetAround(w2, 0, 0, 0, 0);

    hbox_layout.Dolayout();

    EXPECT_EQ(w1->Width(), 1);
    EXPECT_EQ(w2->Width(), 499);
}

TEST(Layout, VBoxLayout)
{
    VBoxLayout vbox_layout;
    vbox_layout.SetGeometry(0, 0, 500, 500);
    TestWidget* w1 = new TestWidget;
    TestWidget* w2 = new TestWidget;
    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(200);
    vbox_layout.AddWidget(w1);
    vbox_layout.AddWidget(w2);

    vbox_layout.Dolayout();
    // default factor is 1
    // alloc height > prefer height
    EXPECT_EQ(w1->X(), 200);
    EXPECT_EQ(w1->Y(), 75);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 150);
    EXPECT_EQ(w2->Y(), 275);
    EXPECT_EQ(w2->Width(), 200);
    EXPECT_EQ(w2->Height(), 200);

    // alloc height < prefer height
    w2->SetPreferHeight(300);

    vbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 200);
    EXPECT_EQ(w1->Y(), 50);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 150);
    EXPECT_EQ(w2->Y(), 200);
    EXPECT_EQ(w2->Width(), 200);
    EXPECT_EQ(w2->Height(), 300);

    // alloc width < prefer width
    w2->SetPreferWidth(600);

    vbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 200);
    EXPECT_EQ(w1->Y(), 50);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 0);
    EXPECT_EQ(w2->Y(), 200);
    EXPECT_EQ(w2->Width(), 500);
    EXPECT_EQ(w2->Height(), 300);

    vbox_layout.SetStrechFactor(w1, 0);

    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(100);
    w2->SetPreferHeight(200);

    vbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 200);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 200);
    EXPECT_EQ(w2->Y(), 200);
    EXPECT_EQ(w2->Width(), 100);
    EXPECT_EQ(w2->Height(), 200);

    // factor > 1
    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(100);
    w2->SetPreferHeight(200);

    vbox_layout.SetAround(w1, 0, 0, 0, 0);
    vbox_layout.SetAround(w2, 0, 0, 0, 0);

    vbox_layout.SetStrechFactor(w1, 2);
    vbox_layout.SetStrechFactor(w2, 3);

    vbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 0);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 500);
    EXPECT_EQ(w1->Height(), 200);

    EXPECT_EQ(w2->X(), 0);
    EXPECT_EQ(w2->Y(), 200);
    EXPECT_EQ(w2->Width(), 500);
    EXPECT_EQ(w2->Height(), 300);

    // limit min height
    vbox_layout.SetStrechFactor(w1, 1);
    vbox_layout.SetStrechFactor(w2, 1);

    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(100);
    w2->SetPreferHeight(200);

    w1->SetLimitMinHeight(500);

    vbox_layout.SetAroundInValid(w1);
    vbox_layout.SetAroundInValid(w2);

    vbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 200);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 500);

    EXPECT_EQ(w2->Height(), 0);

    // limit min width
    w1->SetLimitMinWidth(300);
    
    vbox_layout.Dolayout();

    EXPECT_EQ(w1->X(), 100);
    EXPECT_EQ(w1->Y(), 0);
    EXPECT_EQ(w1->Width(), 300);
    EXPECT_EQ(w1->Height(), 500);

    EXPECT_EQ(w2->Height(), 0);

    // limit max height
    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(100);
    w2->SetPreferHeight(200);

    w1->SetLimitMinHeight(0);
    w1->SetLimitMaxHeight(1);

    vbox_layout.SetStrechFactor(w1, 1);
    vbox_layout.SetStrechFactor(w2, 1);

    vbox_layout.SetAround(w1, 0, 0, 0, 0);
    vbox_layout.SetAround(w2, 0, 0, 0, 0);

    vbox_layout.Dolayout();

    EXPECT_EQ(w1->Height(), 1);
    EXPECT_EQ(w2->Height(), 499);
}

TEST(Layout, HVBoxLayout)
{
    TestWidget* w1 = new TestWidget;
    TestWidget* w2 = new TestWidget;

    w1->SetPreferWidth(100);
    w1->SetPreferHeight(100);
    w2->SetPreferWidth(200);
    w2->SetPreferHeight(200);

    HBoxLayout* hbox_layout = new HBoxLayout;
    hbox_layout->SetGeometry(0, 0, 500, 500);
    hbox_layout->AddWidget(w1);

    VBoxLayout* vbox_layout = new VBoxLayout;
    hbox_layout->AddLayout(vbox_layout);
    vbox_layout->AddWidget(w2);

    hbox_layout->Dolayout();

    EXPECT_EQ(w1->X(), 75);
    EXPECT_EQ(w1->Y(), 200);
    EXPECT_EQ(w1->Width(), 100);
    EXPECT_EQ(w1->Height(), 100);

    EXPECT_EQ(w2->X(), 275);
    EXPECT_EQ(w2->Y(), 150);
    EXPECT_EQ(w2->Width(), 200);
    EXPECT_EQ(w2->Height(), 200);
}
} // namespace ui