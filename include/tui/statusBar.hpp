#pragma once
#include <ncurses.h>

#include "tui/tuiComponent.hpp"

class StatusBar : public TuiComponent
{
   public:
    StatusBar(WINDOW* window);
    ~StatusBar();

    void updateWindow() override;

   private:
    WINDOW* win;
};
