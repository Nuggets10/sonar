#include "tui/tuiManager.hpp"

#include <ncurses.h>

#include <iostream>

#include "tui/equalizerWindow.hpp"
#include "tui/libraryWindow.hpp"
#include "tui/playerWindow.hpp"

TuiManager::TuiManager()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();
    curs_set(0);
    timeout(100);
    getmaxyx(stdscr, height, width);

    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
}

TuiManager::~TuiManager() { endwin(); }

void TuiManager::addComponent(std::unique_ptr<TuiComponent> component)
{
    components.push_back(std::move(component));
}

void TuiManager::display()
{
    char ch;
    bool isRunning{true};
    refresh();

    while (isRunning)
    {
        for (std::unique_ptr<TuiComponent>& component : components)
        {
            component->updateWindow();
        }

        ch = getch();
        if (ch == 'q')
        {
            isRunning = false;
        }
        else if (ch == '1')
        {
            for (std::unique_ptr<TuiComponent>& component : components)
            {
                if (auto* player = dynamic_cast<PlayerWindow*>(component.get()))
                    player->isFocused = false;
                if (auto* library = dynamic_cast<LibraryWindow*>(component.get()))
                    library->isFocused = true;
                if (auto* equalizer = dynamic_cast<EqualizerWindow*>(component.get()))
                    equalizer->isFocused = false;
            }
        }

        else if (ch == '2')
        {
            for (std::unique_ptr<TuiComponent>& component : components)
            {
                if (auto* player = dynamic_cast<PlayerWindow*>(component.get()))
                    player->isFocused = true;
                if (auto* library = dynamic_cast<LibraryWindow*>(component.get()))
                    library->isFocused = false;
                if (auto* equalizer = dynamic_cast<EqualizerWindow*>(component.get()))
                    equalizer->isFocused = false;
            }
        }
        else if (ch == '3')
        {
            for (std::unique_ptr<TuiComponent>& component : components)
            {
                if (auto* player = dynamic_cast<PlayerWindow*>(component.get()))
                    player->isFocused = false;
                if (auto* library = dynamic_cast<LibraryWindow*>(component.get()))
                    library->isFocused = false;
                if (auto* equalizer = dynamic_cast<EqualizerWindow*>(component.get()))
                    equalizer->isFocused = true;
            }
        }
    }
}

WINDOW* TuiManager::createWindow(int height, int width, int y, int x)
{
    WINDOW* window = newwin(height, width, y, x);
    if (height > 1)
    {
        box(window, 0, 0);
    }
    wrefresh(window);
    return window;
}
