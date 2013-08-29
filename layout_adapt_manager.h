#ifndef LAYOUT_ADAPT_MANAGER
#define LAYOUT_ADAPT_MANAGER

#include "layout_base_item.h"

#include <vector>

namespace ui
{
class LayoutAdaptManager
{
    typedef LayoutBaseItem LayoutAdaptItem;
public:
    static LayoutAdaptManager* GetInstance();
    void Push(LayoutAdaptItem* item);
    void Flush();
    void OpenAdapt();
    void CloseAdapt();
    bool AdaptOpened() const;
protected:
    LayoutAdaptManager();
    LayoutAdaptItem* FindPublicItem() const;
private:
    std::vector<LayoutAdaptItem*> layout_adapt_items_;
    bool adapt_opened_;
};
} // namespace ui

#endif // LAYOUT_ADAPT_MANAGER
