#define _CRT_SECURE_NO_WARNINGS
#include "AppMonitor.h"
#include <filesystem>
#include <string>
#include "../helpers/UtilFile.h"
#include "../helpers/UtilString.h"

static Process sServer;
static Process sSpareServer;
static std::string sPort = "0";

bool
Monitor::init() {
    m_console.handleCtrlC(
        Monitor::
            exit);  // if Monitor's execution is aborted via Ctrl+C, reset() cleans up its internal state
    return initMainServer();
}

bool
Monitor::isServerAlive() {
    std::string heartBeatFilePath =
        std::string("./resources/ALIVE" + sServer.pid());

    // If we got heartbeat from Server as a file
    // Remove this file, and wait for another beat
    bool isGotBeat = fileExists(heartBeatFilePath);
    std::filesystem::remove(heartBeatFilePath);

    // Check if we got beat and if Server process didn't crash
    if (isGotBeat || sServer.isAlive()) {
        return true;
    }
    return false;
}

void
Monitor::reset() {
    sServer.terminate();
}

void
Monitor::freeResourceDir() {
    std::string directoryPath = ".\\resources";
    for (const auto& file :
         std::filesystem::directory_iterator(directoryPath)) {
        if (std::filesystem::is_regular_file(file)) {
            if (file.path().filename() != "STATE") {
                std::filesystem::remove_all(file.path());
            }
        }
    }
}

void
Monitor::getAndSetGlobalPort() {
    std::string path = std::string("./resources/CREATED");
    sPort = split(fileReadStr(path), ",")[0];
}

bool
Monitor::initMainServer() {
    char cmd[256] = {};
    sprintf(cmd, "../Server/Server.exe %s", sPort.c_str());
    bool ok = sServer.create(cmd);  // launching Server
    printf(ok ? "monitoring \"%s\"\n" : "error: cannot monitor \"%s\"\n", cmd);
    return ok;
}

bool
Monitor::initSpareServer() {
    char cmd[256] = {};
    sprintf(cmd, "../Server/Server.exe %s", sPort.c_str());
    bool ok = sSpareServer.create(cmd);  // launching Server
    printf(ok ? "monitoring spare pid = %s\n"
              : "error: cannot monitor spare pid = %s\n",
           sSpareServer.pid().c_str());

    sSpareServer.suspend();

    return ok;
}

void
Monitor::exit() {
    sServer.terminate();
    sSpareServer.terminate();
}

void
Monitor::resetSpare() {
    sSpareServer.terminate();
}

void
Monitor::changeSpareToMain() {
    sServer.terminate();

    if (sSpareServer.isAlive()) {
        sServer = sSpareServer;
        sServer.resume();
    } else {
        sSpareServer.terminate();
        initMainServer();
        initSpareServer();
    }
}
