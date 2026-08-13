#pragma once
#include <ncurses.h>
class TuiManager
{
   public:
    int height;
    int width;
    TuiManager();
    ~TuiManager();
    void display();
    WINDOW* createWindow(int height, int width, int y, int x);
};
