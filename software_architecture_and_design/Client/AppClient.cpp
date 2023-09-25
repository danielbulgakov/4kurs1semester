#define _CRT_SECURE_NO_WARNINGS
#include "AppClient.h"
#include "helpers/SocketClient.h"
#include "helpers/UtilString.h"
#include "helpers/UtilFile.h"
#include <map>
#include <Windows.h>

bool Client::send(const std::string& url, const std::string& msg)
{
    SocketClient s;

    while (!s.init() || !s.connect(url)) {
        Sleep(1000);
    }

    printf("sending text message \"%s\"\n", msg.c_str());
    int len = s.sendStr(msg);

    printf("sent %d bytes\n", len);
    return len > 0;
}
