#include "gtest/gtest.h"
#include "layout_base_item.h"
#include "layout.h"
#include "layout_item.h"
#include "widget.h"
#include "box_layout_item.h"
#include "box_layout.h"

namespace ui
{

namespace
{
class TestWidget : public Widget
{
public:
    virtual void AdjustSizes() override {}
    virtual void Relayout() override {}
    virtual SkRect GeometryToAncestor() const override {
        SkRect rect;
        rect.setEmpty();
        return rect;
    };
    virtual void OnDraw(SkCanvas* canvas, const SkRect& clip_rect) {}
};

class TestLayout : public Layout
{
public:
    virtual void AddWidget(Widget* widget) override {}
    virtual bool InsertWidget(int index, Widget *widget) override {return true;}
    virtual bool RemoveWidget(Widget *widget) override {return true;}

    virtual void AddLayout(Layout* layout) override {}
    virtual bool InsertLayout(int index, Layout *layout) override {return true;}
    virtual bool RemoveLayout(Layout *layout) override {return true;}

    virtual void Relayout() {}

    virtual int CalculateLimitMinWidth() override {return 10;}
    virtual int CalculateLimitMinHeight() override {return 10;}
    virtual int CalculateLimitMaxWidth() override {return 100;}
    virtual int CalculateLimitMaxHeight() override {return 100;}
    virtual int CalculatePreferWidth() override {return 50;}
    virtual int CalculatePreferHeight() override {return 50;}

    void Expect() {
        TestWidget w1, w2, w3;
        EXPECT_TRUE(IsEmpty());
        EXPECT_EQ(Count(), 0);
        AddItem(std::make_shared<LayoutItem>(&w1));
        EXPECT_FALSE(IsEmpty());
        EXPECT_EQ(Count(), 1);
        AddItem(std::make_shared<LayoutItem>(&w2));
        EXPECT_EQ(Count(), 2);
        InsertItem(0, std::make_shared<LayoutItem>(&w3));
        EXPECT_EQ(Count(), 3);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), &w3);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), &w1);
        EXPECT_EQ(ItemAt(2)->GetLayoutBaseItem(), &w2);
        RemoveItem(&w3);
        EXPECT_EQ(Count(), 2);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), &w1);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), &w2);
        EXPECT_TRUE(InsertItem(2, std::make_shared<LayoutItem>(&w3)));
        EXPECT_FALSE(InsertItem(2, std::make_shared<LayoutItem>(&w3)));
        EXPECT_EQ(Count(), 3);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), &w1);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), &w2);
        EXPECT_EQ(ItemAt(2)->GetLayoutBaseItem(), &w3);
        RemoveItem(&w3);
        EXPECT_EQ(Count(), 2);
        EXPECT_FALSE(InsertItem(3, std::make_shared<LayoutItem>(&w3)));
        EXPECT_EQ(Count(), 2);
        EXPECT_TRUE(InsertItem(-1, std::make_shared<LayoutItem>(&w3)));
        EXPECT_EQ(Count(), 3);
        EXPECT_EQ(ItemAt(0)->GetLayoutBaseItem(), &w1);
        EXPECT_EQ(ItemAt(1)->GetLayoutBaseItem(), &w3);
        EXPECT_EQ(ItemAt(2)->GetLayoutBaseItem(), &w2);
        EXPECT_TRUE(FindItem(&w3) != nullptr);
        RemoveItem(&w1);
        RemoveItem(&w2);
        RemoveItem(&w3);
        EXPECT_FALSE(FindItem(&w3) != nullptr);
        EXPECT_TRUE(IsEmpty());
        EXPECT_EQ(Count(), 0);
        EXPECT_FALSE(InsertItem(0, nullptr));
        EXPECT_FALSE(RemoveItem(&w3));
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
    TestWidget w1;
    BoxLayoutItem box_item(&w1);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 50);
    EXPECT_EQ(box_item.Y(), 50);
    EXPECT_EQ(box_item.Width(), 0);
    EXPECT_EQ(box_item.Height(), 0);
    w1.SetPreferWidth(50);
    w1.SetPreferHeight(50);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 25);
    EXPECT_EQ(box_item.Y(), 25);
    EXPECT_EQ(box_item.Width(), 50);
    EXPECT_EQ(box_item.Height(), 50);
    box_item.SetAround(0, 0, 0, 0);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 0);
    EXPECT_EQ(box_item.Y(), 0);
    EXPECT_EQ(box_item.Width(), 100);
    EXPECT_EQ(box_item.Height(), 100);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kWestValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 50);
    EXPECT_EQ(box_item.Y(), 0);
    EXPECT_EQ(box_item.Width(), 50);
    EXPECT_EQ(box_item.Height(), 100);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kNorthValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 50);
    EXPECT_EQ(box_item.Y(), 50);
    EXPECT_EQ(box_item.Width(), 50);
    EXPECT_EQ(box_item.Height(), 50);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kSouthValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 50);
    EXPECT_EQ(box_item.Y(), 25);
    EXPECT_EQ(box_item.Width(), 50);
    EXPECT_EQ(box_item.Height(), 50);
    box_item.SetValidGap(BoxLayoutItem::GapValid::kEastValid, false);
    box_item.CalculatePosition(0, 0, 100, 100);
    EXPECT_EQ(box_item.X(), 25);
    EXPECT_EQ(box_item.Y(), 25);
    EXPECT_EQ(box_item.Width(), 50);
    EXPECT_EQ(box_item.Height(), 50);
    
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
    EXPECT_EQ(box_item.X(), 10);
    EXPECT_EQ(box_item.Y(), 10);
    EXPECT_EQ(box_item.Width(), 40);
    EXPECT_EQ(box_item.Height(), 40);
    
    //  move
    box_item.CalculatePosition(10, 10, 100, 100);
    EXPECT_EQ(box_item.X(), 20);
    EXPECT_EQ(box_item.Y(), 20);
    EXPECT_EQ(box_item.Width(), 40);
    EXPECT_EQ(box_item.Height(), 40);

    box_item.CalculatePosition(-10, -10, 100, 100);
    EXPECT_EQ(box_item.X(), 0);
    EXPECT_EQ(box_item.Y(), 0);
    EXPECT_EQ(box_item.Width(), 40);
    EXPECT_EQ(box_item.Height(), 40);

    //west + east > width
    box_item.SetWestSpace(100);
    box_item.CalculatePosition(10, 10, 100, 100);
    EXPECT_EQ(box_item.Width(), 0);
    EXPECT_EQ(box_item.Height(), 40);

    //north + south > height
    box_item.SetNorthSpace(100);
    box_item.CalculatePosition(10, 10, 100, 100);
    EXPECT_EQ(box_item.Width(), 0);
    EXPECT_EQ(box_item.Height(), 0);

    // prefer size with limit
    box_item.SetAround(0, 0, 0, 0);
    w1.SetPreferWidth(100);
    w1.SetLimitMaxWidth(50);
    EXPECT_EQ(box_item.PreferWidth(), 50);
    w1.SetLimitMaxWidth(MAX_LENGTH);
    w1.SetLimitMinWidth(200);
    EXPECT_EQ(box_item.PreferWidth(), 200);

    // prefer size with space
    box_item.SetAround(0, 0, 0, 0);
    w1.SetLimitMinWidth(0);
    w1.SetPreferWidth(100);
    w1.SetLimitMaxWidth(MAX_LENGTH);
    box_item.SetWestSpace(10);
    EXPECT_EQ(box_item.PreferWidth(), 110);
    box_item.SetEastSpace(10);
    EXPECT_EQ(box_item.PreferWidth(), 120);

    w1.SetLimitMinHeight(0);
    w1.SetPreferHeight(100);
    w1.SetLimitMaxHeight(MAX_LENGTH);
    box_item.SetNorthSpace(10);
    EXPECT_EQ(box_item.PreferHeight(), 110);
    box_item.SetSouthSpace(10);
    EXPECT_EQ(box_item.PreferHeight(), 120);
    
    // limit size
    box_item.SetAround(0, 0, 0, 0);
    w1.SetLimitMinWidth(100);
    w1.SetPreferWidth(500);
    w1.SetLimitMaxWidth(200);
    EXPECT_EQ(box_item.LimitMinWidth(), 100);
    EXPECT_EQ(box_item.LimitMaxWidth(), 200);

    w1.SetLimitMinHeight(100);
    w1.SetPreferHeight(500);
    w1.SetLimitMaxHeight(200);
    EXPECT_EQ(box_item.LimitMinHeight(), 100);
    EXPECT_EQ(box_item.LimitMaxHeight(), 200);

    // limit size with space
    box_item.SetAround(10, 20, 10, 20);
    EXPECT_EQ(box_item.LimitMinWidth(), 120);
    EXPECT_EQ(box_item.LimitMaxWidth(), 220);
    EXPECT_EQ(box_item.LimitMinHeight(), 140);
    EXPECT_EQ(box_item.LimitMaxHeight(), 240);

    // empty
    TestWidget w2;
    BoxLayoutItem box_item2(&w2);
    EXPECT_FALSE(box_item2.IsEmpty());
    w2.Hide();
    EXPECT_TRUE(box_item2.IsEmpty());
    w2.Show();
    EXPECT_FALSE(box_item2.IsEmpty());
    
    BoxLayout layout;
    BoxLayoutItem box_item3(&layout);
    EXPECT_TRUE(box_item3.IsEmpty());
    layout.AddWidget(&w2);
    EXPECT_FALSE(box_item3.IsEmpty());
}
} // namespace ui