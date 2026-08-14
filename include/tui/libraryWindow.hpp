#pragma once
#include <ncurses.h>

#include "tui/tuiComponent.hpp"

class LibraryWindow : public TuiComponent
{
   public:
    LibraryWindow(WINDOW* window);
    ~LibraryWindow();

    void updateWindow() override;
    bool isFocused;

   private:
    WINDOW* win;
};
