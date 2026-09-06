#pragma once
#include <ncurses.h>

#include <string>
#include <vector>

#include "tui/tuiComponent.hpp"

class LibraryWindow : public TuiComponent
{
   public:
    LibraryWindow(WINDOW* window);
    ~LibraryWindow();

    void updateWindow() override;
    void addFiles(std::vector<std::string> files);
    void increaseIndex();
    void decreaseIndex();
    void selectAudio();
    bool isFocused;

   private:
    WINDOW* win;
    std::vector<std::string> files;
    size_t topVisibleIndex;
    size_t index;
};
