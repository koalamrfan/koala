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
    void Drive();
    void OpenAdapt();
    void CloseAdapt();
    bool AdaptOpened() const;
protected:
    LayoutAdaptManager();
private:
    bool adapt_opened_;
};
} // namespace ui

#endif // LAYOUT_ADAPT_MANAGER
