#pragma once
#include <ncurses.h>

class TuiComponent
{
   public:
    virtual ~TuiComponent() = default;
    virtual void updateWindow() = 0;
};
