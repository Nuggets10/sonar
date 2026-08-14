#include "tui/libraryWindow.hpp"

LibraryWindow::LibraryWindow(WINDOW* window) : isFocused(true), win(window) {}

LibraryWindow::~LibraryWindow() { delwin(win); }

void LibraryWindow::updateWindow()
{
    box(win, 0, 0);
    if (isFocused)
    {
        wattron(win, COLOR_PAIR(1) | A_BOLD);
    }
    mvwaddstr(win, 0, 2, "[1] Library");
    if (isFocused)
    {
        wattroff(win, COLOR_PAIR(1) | A_BOLD);
    }
    wrefresh(win);
}
