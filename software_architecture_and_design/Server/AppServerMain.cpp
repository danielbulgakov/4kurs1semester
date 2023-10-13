#include "windows.h"
#include "AppServer.h"
#include <filesystem>

#pragma comment(lib, "Ws2_32.lib")

void fix() {
    // Check if the folder already exists
    if (std::filesystem::exists("resources")) {
        // Remove all files and subdirectories within the folder
        for (const auto& entry : std::filesystem::directory_iterator("resources")) {
            // Check if the filename is "STATE"
            if (entry.path().filename() != "STATE") {
                if (std::filesystem::is_directory(entry.path())) {
                    std::filesystem::remove_all(entry.path());
                } else {
                    std::filesystem::remove(entry.path());
                }
            }
        }
    } else {
        // Create the directory
        std::filesystem::create_directory("resources");
    }
}



int main (int argc, char *argv[])
{
    fix();
    int port = argc > 1 ? atoi(argv[1]) : 0;
    Server s;
    while(!s.init(port))
        Sleep(1000);
    s.run();
}