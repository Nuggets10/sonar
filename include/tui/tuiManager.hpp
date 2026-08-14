#pragma once
#include <ncurses.h>

#include <memory>
#include <vector>

#include "tui/tuiComponent.hpp"

class TuiManager
{
   public:
    int height;
    int width;
    TuiManager();
    ~TuiManager();
    void display();
    void addComponent(std::unique_ptr<TuiComponent> component);
    WINDOW* createWindow(int height, int width, int y, int x);

   private:
    std::vector<std::unique_ptr<TuiComponent>> components;
};
