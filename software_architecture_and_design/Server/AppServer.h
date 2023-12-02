#pragma once
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "helpers/SocketServer.h"
#include "helpers/UserDataBase.h"

// Server that accepts connections from Clients and Viewers.
// Clients can upload text and images to Server.
class Server {
   public:
    Server() = default;
    virtual ~Server() = default;
    bool init(int port = 0);  // initialize server socket, load configuration
    void run();               // accept incoming connections, receive their data and send responses
    void sendEntireFeed(std::shared_ptr<Socket>& s);
    void sendLastEntryInFeed(std::shared_ptr<Socket>& s);
    void updateLastEntryForAll();

   private:
    SocketServer m_socket;                               // server socket
    std::vector<std::string> m_data;                     // representation of uploaded data
    std::vector<std::shared_ptr<Socket>> m_subscribers;  // storage of Viewers receiving push notifications
    UserDatabase userDB;

    std::string pendingLogin;
    std::string pendingPassword;
};
