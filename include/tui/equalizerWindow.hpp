#pragma once
#include <ncurses.h>

#include "tui/tuiComponent.hpp"

class EqualizerWindow : public TuiComponent
{
   public:
    EqualizerWindow(WINDOW* window);
    ~EqualizerWindow();

    void updateWindow() override;
    bool isFocused;

   private:
    WINDOW* win;
};
