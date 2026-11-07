#pragma once
#include <ncurses.h>

#include <string>

#include "tui/tuiComponent.hpp"
#include "tui/libraryWindow.hpp"

class PlayerWindow : public TuiComponent
{
public:
    PlayerWindow(WINDOW* window, LibraryWindow& libWindow);
    ~PlayerWindow();

    void updateAudioName(bool isValid, std::string audioName);
    void updateAutoPlay();
    void updateWindow() override;
    void increaseIndex();
    void decreaseIndex();
    void changeVolume(bool isLowering);
    void increaseAutoPlay();
    void togglePause();
    int getIndex() const {
        return index;
    }
    bool isFocused;

private:
    WINDOW* win;
    LibraryWindow& libWindow;
    size_t index;
    void clearTui();
    void updateOptions();
    void updateVolume();
    void updateTime(float current, float total);
    int volume;
};
