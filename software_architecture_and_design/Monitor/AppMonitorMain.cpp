#include <windows.h>
#include <iostream>
#include <filesystem>
#include "AppMonitor.h"


int main()
{
    Monitor m;
    bool firstStart = true;
    if(!m.init()) {
        std::cerr << "Monitor initialization failed!\n";
        return 1;
    }
    Sleep(1000);
    Monitor::getAndSetPort();
    Monitor::freeResourceDir();
    m.initSpareServer();


    while (1) {
        if(!m.check() && firstStart) {
            m.reset();
            m.init();
            Monitor::freeResourceDir();
        } else if (!m.check()) {
            m.resetSpareServer();
            Monitor::freeResourceDir();
        } else {
            firstStart = false;
        }

        Sleep(3000);
    }
}