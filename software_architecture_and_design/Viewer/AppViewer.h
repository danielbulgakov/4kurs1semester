#pragma once
#include <string>
#include <vector>
#include "helpers/Console.h"
#include "helpers/SocketClient.h"

// console app that displays real-time content of Server feed. Text is displayed in console windows. Images are opened by default viewer app.
// Pressing ESC activates typing mode, when it is possible to type text message and send it to Server by pressing ENTER.
// The app uses user's login and password to upload data.
class Viewer {
   public:
    Viewer() = default;
    virtual ~Viewer() = default;

    bool init();  // establish client socket and load configuration
    void run();   // receive server and user updates in the loop

   private:
    char m_url[256] = "127.0.0.1:12345";
    SocketClient m_socket;            // client socket
    std::vector<std::string> m_data;  // representation of server feed
    Console m_console;
};
