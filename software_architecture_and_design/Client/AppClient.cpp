#define _CRT_SECURE_NO_WARNINGS
#include "AppClient.h"

#include "../helpers/UtilString.h"
#include <chrono>
#include <thread>

bool Client::send(const std::string& msg)
{
    if (!isConnected) return false;
    int len;
    printf("sending text message \"%s\"\n", msg.c_str());

    len = s.sendStr(msg);

    printf("sent %d bytes\n", len);
    return len > 0;
}

std::string Client::recieve() {
    if (!isConnected) return {};
    s.recv();
    std::string str = s.data();
    return str;
}

bool Client::connect(const std::string &url) {
    auto start = std::chrono::high_resolution_clock::now();
    while(!s.init() || !s.connect(url))
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        if (elapsed.count() >= 60.0) // if 60 seconds have passed
        {
            printf("Server not available. Stopping retries.\n");
            isConnected = false;
            return false;
        }
        printf("Server not available. Retrying...\n");
        std::this_thread::sleep_for(std::chrono::seconds(5)); // wait for 5 second before retrying
    }
    isConnected = true;
    return true;
}
