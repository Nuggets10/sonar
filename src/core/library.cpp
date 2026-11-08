#include "core/library.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "tui/libraryWindow.hpp"

std::vector<std::string> listFiles(std::string path)
{
    std::vector<std::string> files;

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        for (std::filesystem::directory_entry file : std::filesystem::directory_iterator(path))
        {
            if (file.is_regular_file())
            {
                std::string extension = file.path().extension().string();

                if (extension == ".mp3" or extension == ".wav" or extension == ".flac")
                {
                    files.push_back(file.path().filename().string());
                }
            }
        }
    }

    return files;
}

void initLibrary(LibraryWindow& libWin)
{
    std::string dir{std::filesystem::current_path().string()};
    std::vector<std::string> files = listFiles(dir);
    files.shrink_to_fit();
    std::sort(files.begin(), files.end());
    libWin.addFiles(files);
}
