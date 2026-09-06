#include "tui/libraryWindow.hpp"

#include <filesystem>
#include <string>
#include <vector>

#include "core/player.hpp"

LibraryWindow::LibraryWindow(WINDOW* window)
    : isFocused(true), win(window), topVisibleIndex(0), index(0)
{
}

LibraryWindow::~LibraryWindow() { delwin(win); }

void LibraryWindow::updateWindow()
{
    werase(win);
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

    int maxRows = getmaxy(win) - 2;

    if (index < topVisibleIndex)
    {
        topVisibleIndex = index;
    }
    else if (index >= topVisibleIndex + maxRows)
    {
        topVisibleIndex = index - maxRows + 1;
    }

    int y = 1;
    size_t end = std::min(files.size(), (size_t)(topVisibleIndex + maxRows));
    for (size_t i = topVisibleIndex; i < end; i++)
    {
        if (i == index)
        {
            wattron(win, COLOR_PAIR(4));
            mvwprintw(win, y++, 1, files[i].c_str());
            for (int j{0}; j < getmaxx(win) - (int)files[i].size() - 2; j++)
            {
                wprintw(win, " ");
            }
            wattroff(win, COLOR_PAIR(4));
        }
        else
        {
            mvwprintw(win, y++, 1, files[i].c_str());
        }
    }

    wrefresh(win);
}

void LibraryWindow::increaseIndex()
{
    if (index < files.size() - 1)
    {
        index += 1;
    }
}
void LibraryWindow::decreaseIndex()
{
    if (index > 0)
    {
        index -= 1;
    }
}

void LibraryWindow::addFiles(std::vector<std::string> files)
{
    this->files = files;
    wrefresh(win);
}

void LibraryWindow::selectAudio()
{
    playAudio(std::filesystem::current_path().string() + "/" + files[index]);
}
