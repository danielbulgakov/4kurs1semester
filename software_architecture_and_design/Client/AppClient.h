#pragma once
#include <string>
#include "SocketClient.h"

// command-line Client app that can send messages to Server.
class Client {
   private:
    SocketClient s;

   public:
    Client() = default;
    virtual ~Client() = default;

    bool send(const std::string& url,
              const std::string& msg);  // sends message to Server
    const char* recieve();
};
