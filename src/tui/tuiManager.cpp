#include "tui/tuiManager.hpp"

#include <ncurses.h>

#include <iostream>

TuiManager::TuiManager()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);
    getmaxyx(stdscr, height, width);
}

TuiManager::~TuiManager() { endwin(); }

void TuiManager::display()
{
    char ch;
    bool isRunning{true};

    while (isRunning)
    {
        ch = getch();
        if (ch == 'q')
        {
            isRunning = false;
        }
        refresh();
    }
}

WINDOW* TuiManager::createWindow(int height, int width, int y, int x)
{
    WINDOW* window = newwin(height, width, y, x);
    box(window, 0, 0);
    wrefresh(window);  // Refreshes to show the border
                       // Handle future refreshes in the sub windows scripts
    return window;
}
