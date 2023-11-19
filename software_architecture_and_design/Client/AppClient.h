#pragma once
#include <string>
#include "helpers/SocketClient.h"
// command-line Client app that can send messages to Server.
class Client
{
private:
    SocketClient s;
    bool isConnected = false;
public:
    Client() = default;
    virtual ~Client() = default;
    bool connect(const std::string& url); // recieve message from server
    bool send(const std::string& msg); // sends message to Server
    std::string recieve();
};
