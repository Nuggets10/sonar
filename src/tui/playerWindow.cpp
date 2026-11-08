#include "tui/playerWindow.hpp"

#include <string>

#include "core/player.hpp"

PlayerWindow::PlayerWindow(WINDOW* window, LibraryWindow& libWindow) : isFocused(false), win(window), libWindow(libWindow), index(0), volume(10)
{
    clearTui();
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, 1, 1, "No file is being played");
    wattroff(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, 4, 1, "Pause");
    mvwprintw(win, 5, 1, "Autoplay: none");
    mvwprintw(win, 6, 1, "Volume +/-");
}

PlayerWindow::~PlayerWindow()
{
    delwin(win);
}

void PlayerWindow::clearTui()
{
    wmove(win, 1, 1);
    std::string titleSpaces(getmaxx(win) - 2, ' ');
    mvwaddstr(win, 1, 1, titleSpaces.c_str());
    mvwprintw(win, 2, 1, "00:00:00 - HH:MM:SS");
    mvwprintw(win, 3, 1, "[");
    std::string progressBarPlaceholder(getmaxx(win) - 4, '.');
    mvwprintw(win, 3, 2, "%s", progressBarPlaceholder.c_str());
    mvwprintw(win, 3, getmaxx(win) - 2, "]");
    mvwprintw(win, 8, 1, "[");
    mvwprintw(win, 8, 2, "%s", progressBarPlaceholder.c_str());
    mvwprintw(win, 8, getmaxx(win) - 2, "]");
}

void PlayerWindow::updateTime(float current, float total)
{
    int curSec = (int)current;
    int curH = curSec / 3600;
    int curM = (curSec % 3600) / 60;
    int curS = curSec % 60;

    int totSec = (int)total;
    int totH = totSec / 3600;
    int totM = (totSec % 3600) / 60;
    int totS = totSec % 60;

    char timeStr[40];
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d - %02d:%02d:%02d", curH, curM, curS, totH,
             totM, totS);
    mvwprintw(win, 2, 1, "%s", timeStr);

    int barWidth = getmaxx(win) - 4;
    int progress = 0;

    if (total > 0)
    {
        progress = (int)((current / total) * barWidth);
    }

    if (progress > barWidth)
    {
        progress = barWidth;
    }

    wattron(win, COLOR_PAIR(4) | A_BOLD);

    for (int i = 0; i < progress; ++i)
    {
        if (i != 0)
        {
            mvwaddch(win, 3, 1 + i, '=');
        }

        mvwaddch(win, 3, 2 + i, '>');
    }

    wattroff(win, COLOR_PAIR(4) | A_BOLD);

    for (int i = progress; i < barWidth; ++i)
    {
        mvwaddch(win, 3, 2 + i, '.');
    }
}

void PlayerWindow::updateVolume()
{
    mvwprintw(win, 7, 1, "                   ");
    mvwprintw(win, 7, 1, "Volume: %d/20", volume);

    if (volume > 10)
    {
        wattron(win, COLOR_PAIR(2) | A_BOLD);
        mvwprintw(win, 7, 15, "BOOST");
        wattroff(win, COLOR_PAIR(2) | A_BOLD);
    }

    int barWidth = getmaxx(win) - 4;
    int progress = (int)((volume / 20.0) * barWidth);

    if (progress > barWidth)
    {
        progress = barWidth;
    }

    for (int i = 0; i < barWidth; ++i)
    {
        int colorPair;

        if (i < barWidth / 3)
        {
            colorPair = COLOR_PAIR(5);
        }
        else
            if (i < (2 * barWidth) / 3)
            {
                colorPair = COLOR_PAIR(6);
            }
            else
            {
                colorPair = COLOR_PAIR(7);
            }

        if (i < progress)
        {
            wattron(win, colorPair | A_BOLD);
            mvwaddch(win, 8, 2 + i, ' ');
            wattroff(win, colorPair | A_BOLD);
        }
        else
        {
            mvwaddch(win, 8, 2 + i, '.');
        }
    }
}

void PlayerWindow::updateAutoPlay()
{
    mvwprintw(win, 5, 10, "         ");

    switch (getAutoPlayMode())
    {
        case 0:
            mvwprintw(win, 5, 10, " none");
            break;

        case 1:
            mvwprintw(win, 5, 10, " repeat");
            break;

        case 2:
            mvwprintw(win, 5, 10, " linear");
            break;

        case 3:
            mvwprintw(win, 5, 10, " shuffle");
            break;
    }
}

void PlayerWindow::increaseAutoPlay()
{
    if (getAutoPlayMode() == 3)
    {
        setAutoPlayMode(0);
    }
    else
    {
        setAutoPlayMode(getAutoPlayMode() + 1);
    }
}

void PlayerWindow::togglePause()
{
    if (getPauseState())
    {
        togglePauseAudio();
        mvwprintw(win, 4, 1, "      ");
        mvwprintw(win, 4, 1, "Pause");
    }
    else
    {
        togglePauseAudio();
        mvwprintw(win, 4, 1, "Resume");
    }
}

void PlayerWindow::updateOptions()
{
    const char *pauseLabel = getPauseState() ? "Resume" : "Pause";

    wattron(win, COLOR_PAIR(4) | A_BOLD);

    if (index == 0)
    {
        mvwprintw(win, 4, 1, "%-6s", pauseLabel);
        wattroff(win, COLOR_PAIR(4) | A_BOLD);
        mvwprintw(win, 5, 1, "Autoplay: shuffle");
        mvwprintw(win, 6, 1, "Volume +/-");
    }
    else
        if (index == 1)
        {
            mvwprintw(win, 5, 1, "Autoplay: ");
            wattroff(win, COLOR_PAIR(4) | A_BOLD);
            mvwprintw(win, 4, 1, "%-6s", pauseLabel);
            mvwprintw(win, 6, 1, "Volume +/-");
        }
        else
            if (index == 2)
            {
                mvwprintw(win, 6, 1, "Volume +/-");
                wattroff(win, COLOR_PAIR(4) | A_BOLD);
                mvwprintw(win, 4, 1, "%-6s", pauseLabel);
                mvwprintw(win, 5, 1, "Autoplay: shuffle");
            }
}

void PlayerWindow::updateWindow()
{
    float current = 0, total = 0;

    if (getAudioTime(&current, &total))
    {
        updateTime(current, total);

        if (total > 0 && current >= total - 0.1f)
        {
            if (getAutoPlayMode() == 1)
            {
                restartAudio();
            }
            else
                if (getAutoPlayMode() == 2)
                {
                    libWindow.increaseIndex();
                    libWindow.selectAudio();
                }
                else
                    if (getAutoPlayMode() == 3)
                    {
                        libWindow.randomizeIndex();
                        libWindow.selectAudio();
                    }
        }
    }

    updateVolume();
    updateOptions();
    updateAutoPlay();

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

void PlayerWindow::updateAudioName(bool isValid, std::string fileName)
{
    clearTui();

    if (isValid)
    {
        fileName = fileName.substr(fileName.find_last_of('/') + 1,
                                   fileName.find_last_of('.') - (fileName.find_last_of('/') + 1));

        if (fileName.length() > (size_t)getmaxx(win) - 2)
        {
            if (getmaxx(win) - 2 > 3)
            {
                fileName = fileName.substr(0, getmaxx(win) - 2 - 3) + "...";
            }
            else
            {
                fileName = fileName.substr(0, getmaxx(win) - 2);
            }
        }

        mvwaddstr(win, 1, 1, fileName.c_str());
    }
    else
    {
        wattron(win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(win, 1, 1, "Error while opening file");
        wattroff(win, COLOR_PAIR(3) | A_BOLD);
    }
}

void PlayerWindow::increaseIndex()
{
    if (index < 2)
    {
        index += 1;
    }
}

void PlayerWindow::decreaseIndex()
{
    if (index > 0)
    {
        index -= 1;
    }
}

void PlayerWindow::changeVolume(bool isLowering)
{
    if (index != 2)
    {
        return;
    }

    if (isLowering)
    {
        decreaseVolume();

        if (volume > 0)
        {
            volume--;
        }
    }
    else
    {
        increaseVolume();

        if (volume < 20)
        {
            volume++;
        }
    }
}
