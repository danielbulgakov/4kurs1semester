#include "Appclient.h"
#include <iostream>

#include "../helpers/UtilString.h"
#include "../helpers/UtilFile.h"
#include "../helpers/Message.h"

#pragma comment(lib, "Ws2_32.lib")

int main (int argc, char *argv[])
{
    int maxTryes = 5;
    int tries = 0;

    if(argc < 4 || split(argv[1], ":").size() != 2)
    {
        printf("USAGE: Client.exe <HOST:PORT> <LOGIN> <PASSWORD>\n\n");
        printf("Example: Client.exe 192.168.1.1:12345 ivan 12345\n");
        return 0;
    }
    
    std::string msg = argv[2];
    for(int i = 3; i < argc; i++)
        msg += std::string(" ") + argv[i];

    Client c;
    Token t;
    std::string url = argv[1];
    c.connect(url);

    while (tries++ <= maxTryes) {
        std::string log, pass;
        std::string send;
        std::cin >> log >> pass;
        Message m = Message(MType::System, Token(false), send.append(log).append(" ").append(pass));
        c.send(m.stringify());
        m.destringify(c.recieve());
        if (!m.getToken().isEmpty()) {
            t = m.getToken();
        }
        std::cout << m.getContent();
    }
    if (tries >= maxTryes) return 1;

    while (true) {
        std::string send;
        std::cin >> send;

        if (fileExists(send)) {
            c.send(
                   Message(MType::File, t, std::filesystem::path(send).filename().string(), getFileStr(send))
                        .stringify()
                   );
        } else {
            c.send(
                   Message(MType::Msg, t, getFileStr(send))
                        .stringify()
                   );
        }

    }

}