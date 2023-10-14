#define _CRT_SECURE_NO_WARNINGS
#include "AppClient.h"
#include "helpers/SocketClient.h"
#include "../helpers/UtilString.h"
#include "../helpers/UtilFile.h"
#include <map>
#include <chrono>
#include <thread>

bool Client::send(const std::string& url, const std::string& msg)
{
    SocketClient s;

    printf("%s", msg.c_str());

    auto start = std::chrono::high_resolution_clock::now();
    while(!s.init() || !s.connect(url))
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        if (elapsed.count() >= 60.0) // if 60 seconds have passed
        {
            printf("Server not available. Stopping retries.\n");
            return false;
        }
        printf("Server not available. Retrying...\n");
        std::this_thread::sleep_for(std::chrono::seconds(5)); // wait for 5 second before retrying
    }

    int len;
    printf("sending text message \"%s\"\n", msg.c_str());
    len = s.sendStr(msg);

    printf("sent %d bytes\n", len);
    return len > 0;
}
