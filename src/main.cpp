#include <iostream>
#include <string>

#include "core/library.hpp"
#include "core/player.hpp"
#include "tui/equalizerWindow.hpp"
#include "tui/libraryWindow.hpp"
#include "tui/playerWindow.hpp"
#include "tui/statusBar.hpp"
#include "tui/tuiManager.hpp"
#include "version.hpp"

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        bool v_flag{false};

        for (int i{1}; i < argc; i++)
        {
            std::string_view arg{argv[i]};

            if (arg == "--v" or arg == "--version")
            {
                v_flag = true;
            }
            else
            {
                std::cerr << "Unknown argument '" << arg << "'" << std::endl;
                return 1;
            }
        }

        if (v_flag)
        {
            std::cout << "Version " << PROJECT_VERSION << std::endl;
            return 0;
        }
    }

    TuiManager tuiManager;

    WINDOW* window = tuiManager.createWindow(tuiManager.height - 1, tuiManager.width / 3, 0, 0);
    std::unique_ptr<LibraryWindow> libWindow = std::make_unique<LibraryWindow>(window);
    LibraryWindow& libWindowRef = *libWindow;
    tuiManager.addComponent(std::move(libWindow));

    initLibrary(libWindowRef);
    window = tuiManager.createWindow(tuiManager.height / 2 - 2, 2 * tuiManager.width / 3, 0,
                                     tuiManager.width / 3);
    auto playerWindow = std::make_unique<PlayerWindow>(window, libWindowRef);
    PlayerWindow& playerWindowRef = *playerWindow;
    tuiManager.addComponent(std::move(playerWindow));

    initPlayer(playerWindowRef);

    window = tuiManager.createWindow(tuiManager.height / 2 + 1, 2 * tuiManager.width / 3,
                                     tuiManager.height / 2 - 2, tuiManager.width / 3);
    tuiManager.addComponent(std::make_unique<EqualizerWindow>(window));

    window = tuiManager.createWindow(1, tuiManager.width, tuiManager.height - 1, 0);
    tuiManager.addComponent(std::make_unique<StatusBar>(window));

    tuiManager.display();
    uninitPlayer();
    return 0;
}
