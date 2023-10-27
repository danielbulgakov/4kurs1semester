#include "windows.h"
#include "AppServer.h"
#include <filesystem>

#pragma comment(lib, "Ws2_32.lib")

void fix() {
    std::string directoryPath = ".\\resources";
    for (const auto& file : std::filesystem::directory_iterator(directoryPath)) {
        if (std::filesystem::is_regular_file(file)) {
            if (file.path().filename() != "STATE") {
                std::filesystem::remove_all(file.path());
            }
        }
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