#pragma once
#include "helpers/Console.h"

// Monitor app that manages Server's lifecycle and monitors its state
class Monitor {
   public:
    Monitor() = default;
    virtual ~Monitor() = default;
    bool init();           // launches Server
    bool isServerAlive();  // checks Server state
    void reset();          // terminates irresponsive Server

    static void exit();
    /** Updates for Spare Server */
    bool initMainServer();
    bool initSpareServer();
    void resetSpare();
    void changeSpareToMain();

    void getAndSetGlobalPort();
    void freeResourceDir();

   private:
    Console m_console;
};
