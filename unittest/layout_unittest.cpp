#include "gtest/gtest.h"
#include "layout_base_item.h"
#include "layout.h"
#include "layout_item.h"
#include "widget.h"

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
} // namespace ui