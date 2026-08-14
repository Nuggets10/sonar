#pragma once
#include <ncurses.h>

#include "tui/tuiComponent.hpp"

class PlayerWindow : public TuiComponent
{
   public:
    PlayerWindow(WINDOW* window);
    ~PlayerWindow();

    void updateWindow() override;
    bool isFocused;

   private:
    WINDOW* win;
};
