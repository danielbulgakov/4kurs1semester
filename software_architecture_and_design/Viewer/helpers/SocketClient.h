#pragma once
#include <string>
#include <vector>
#include "Socket.h"

// client-side socket class. Can connect to server-side socket.
class SocketClient : public Socket {
   public:
    SocketClient() = default;
    virtual ~SocketClient() = default;
    bool connect(
        const std::string&
            url);  //connect to server-side socket. Supported URLs are in form HOST:PORT, e.g. google.com:443
};
