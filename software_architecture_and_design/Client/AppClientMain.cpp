#include <cstring>
#include <iostream>
#include <vector>
#include "../helpers/Message.h"
#include "../helpers/UtilFile.h"
#include "../helpers/UtilString.h"
#include "Appclient.h"

#pragma comment(lib, "Ws2_32.lib")

bool isLoginStage = true;
std::string auth;
std::string perm;
std::string username;

bool
hasTokenTypeToken(std::string data, std::string find) {
    size_t tokenPos = data.find(find);
    return tokenPos != std::string::npos;
}

int
main(int argc, char* argv[]) {
    if (argc < 2 || split(argv[1], ":").size() != 2) {
        printf("USAGE: Client.exe <HOST:PORT>\n\n");
        printf("Example: Client.exe 192.168.1.1:12345\n");
        return 0;
    }

    Client c;

    while (isLoginStage) {
        std::cout << "Enter your username: ";
        std::cin >> username;

        // Get password from the console (note: this is a simple example, in a real system, you should use more secure methods)
        std::cout << "Enter your password: ";
        std::string password;
        std::cin >> password;

        std::string send;
        send.append("username: ").append(username).append(" ").append("password: ").append(password);

        Message m = Message(SYSTEM, send);
        std::string serialized = Message::serialize(m);

        if (c.send(argv[1], serialized) == 0) {
            continue;
        }

        std::string data = std::string(c.recieve());

        if (hasTokenTypeToken(data, "token: ")) {
            size_t tokenPos = data.find("token: ") + std::strlen("token: ");
            std::string temp = data.substr(tokenPos);

            auth = split(temp, ":")[0];
            perm = split(temp, ":")[1];

            isLoginStage = false;
            break;
        } else if (hasTokenTypeToken(data, "REGISTER")) {
            std::string buff;
            std::cout << "Do you want to register [yes/no]" << std::endl;
            std::cin >> buff;

            if (buff[0] == 'y') {
                Message m = Message(SYSTEM, "YES");
                std::string serialized = Message::serialize(m);
                if (c.send(argv[1], serialized) == 0) {
                    std::cout << "ERROR" << std::endl;
                    continue;
                }
            } else {
                return 2;
            }

        } else {
            std::cout << "Received data: " << data << std::endl;
        }
    }

    std::cout << "\nPermissions: " << perm << "\n";

    while (true) {
        std::string buff;

        // Needed ignore to not let cin send empty line in the beginning of loop
        // For some reason cin found in stream \n and send it to server as new message
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n" << username << ": " << std::flush;
        std::cin >> buff;

        if (auth.empty())
            return 1;

        if (buff.empty())
            continue;

        if (fileExists(buff)) {
            if (perm != "admin") {
                std::cout << "Not enough permissions" << std::endl;
                continue;
            }

            Message m = Message(FILE_TRANSFER, auth, std::filesystem::path(buff).filename().string(), getFileStr(buff));
            std::string serialized = Message::serialize(m);
            c.send(argv[1], serialized);
        } else {
            Message m = Message(SIMPLE, auth, buff);
            std::string serialized = Message::serialize(m);
            c.send(argv[1], serialized);
        }
    }
}