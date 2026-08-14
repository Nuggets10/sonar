#include "tui/statusBar.hpp"

StatusBar::StatusBar(WINDOW* window) : win(window) {}

StatusBar::~StatusBar() { delwin(win); }

void StatusBar::updateWindow()
{
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 0, 0, "Up: w | Down: s | Left: a | Right: d | Play/Pause: e | Quit: q");
    for (int i{0}; i < getmaxx(win) - 75; i++)
    {
        wprintw(win, " ");
    }
    wprintw(win, "Contribute: c");
    wattroff(win, COLOR_PAIR(4));
    wrefresh(win);
}
