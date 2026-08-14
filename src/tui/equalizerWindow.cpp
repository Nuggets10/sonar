#include "tui/equalizerWindow.hpp"

EqualizerWindow::EqualizerWindow(WINDOW* window) : isFocused(false), win(window) {}

EqualizerWindow::~EqualizerWindow() { delwin(win); }

void EqualizerWindow::updateWindow()
{
    box(win, 0, 0);
    if (isFocused)
    {
        wattron(win, COLOR_PAIR(1) | A_BOLD);
    }
    mvwaddstr(win, 0, 2, "[3] Equalizer");
    if (isFocused)
    {
        wattroff(win, COLOR_PAIR(1) | A_BOLD);
    }
    wrefresh(win);
}
