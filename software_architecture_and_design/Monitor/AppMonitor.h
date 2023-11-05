#pragma once
#include "helpers/Console.h"

// Monitor app that manages Server's lifecycle and monitors its state
class Monitor
{
public:
    Monitor() = default;
    virtual ~Monitor() = default;
    bool init(); // launches Server
    bool check(); // checks Server state
    void reset(); // terminates irresponsive Server

    bool initSpareServer();
    bool activateSpareServer();
    void resetSpareServer();

    static void exit();

    static void getAndSetPort();
    static void freeResourceDir();

private:
    Console m_console;
};
