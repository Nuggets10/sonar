#include <iostream>
#include <string>

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
        bool h_flag{false};
        bool s_flag{false};

        for (int i{1}; i < argc; i++)
        {
            std::string arg{argv[i]};
            if (arg == "--v" or arg == "--version")
            {
                v_flag = true;
            }
            else if (arg == "--h" or arg == "--help")
            {
                h_flag = true;
            }
            else if (arg == "--s" or arg == "--settings")
            {
                s_flag = true;
            }
            else
            {
                std::cerr << "\033[91mUnknown argument '" << arg << "'" << std::endl;
                return 1;
            }
        }
        if (v_flag)
        {
            std::cout << "Version \033[93m" << PROJECT_VERSION << "\033[0m" << std::endl;
        }
        if (h_flag)
        {
            std::cout << "h accepted";
        }
        if (s_flag)
        {
            std::cout << "s accepted";
        }
    }

    TuiManager tuiManager;

    WINDOW* window = tuiManager.createWindow(tuiManager.height - 1, tuiManager.width / 3, 0, 0);
    tuiManager.addComponent(std::make_unique<LibraryWindow>(window));

    window = tuiManager.createWindow(tuiManager.height / 2 - 2, 2 * tuiManager.width / 3, 0,
                                     tuiManager.width / 3);
    tuiManager.addComponent(std::make_unique<PlayerWindow>(window));

    window = tuiManager.createWindow(tuiManager.height / 2 + 1, 2 * tuiManager.width / 3,
                                     tuiManager.height / 2 - 2, tuiManager.width / 3);
    tuiManager.addComponent(std::make_unique<EqualizerWindow>(window));

    window = tuiManager.createWindow(1, tuiManager.width, tuiManager.height - 1, 0);
    tuiManager.addComponent(std::make_unique<StatusBar>(window));

    tuiManager.display();
    return 0;
}
