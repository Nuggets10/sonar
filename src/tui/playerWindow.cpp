#include "tui/playerWindow.hpp"

PlayerWindow::PlayerWindow(WINDOW* window) : isFocused(false), win(window) {}

PlayerWindow::~PlayerWindow() { delwin(win); }

void PlayerWindow::updateWindow()
{
    box(win, 0, 0);
    if (isFocused)
    {
        wattron(win, COLOR_PAIR(1) | A_BOLD);
    }
    mvwaddstr(win, 0, 2, "[2] Player");
    if (isFocused)
    {
        wattroff(win, COLOR_PAIR(1) | A_BOLD);
    }
    wrefresh(win);
}
