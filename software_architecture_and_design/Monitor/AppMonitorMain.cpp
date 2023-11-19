#include <windows.h>
#include <iostream>
#include <filesystem>
#include "AppMonitor.h"


int main()
{
    Monitor m;

    /** Free all files before start up except for STATE */
    m.freeResourceDir();

    if(!m.init()) {
        std::cerr << "Monitor initialization failed!\n";
        if (std::filesystem::exists(std::string("./resources/CREATED"))) {
            std::cerr << "Server initialization failed!\n";
        }
        return 1;
    }

    Sleep(1000);
    m.getAndSetGlobalPort();
    m.initSpareServer();

    while (1) {
        if(!m.isServerAlive()) {
            m.freeResourceDir();
            m.changeSpareToMain();
            m.initSpareServer();
        }
        Sleep(1000);
    }

}