#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <iostream>


#include "AppViewer.h"
#include "../helpers/UtilFile.h"
#include "../helpers/UtilString.h"
#include "helpers/Socket.h"

// get some input string from user and store it in a variable
void
getInput(char* param, const char* name) {
    printf("Enter %s or press ENTER to use saved value (\"%s\")\n", name,
           param);
    char buf[256] = {};
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        char val[256] = {};
        sscanf(buf, "%s\r\n", val);
        memcpy(param, val, 256);
    }
}

void
runApp(
    std::string
        cmd)  // run application, possibly with arguments. Example: runApp("AppServer.exe 12345");
{
    system(cmd.c_str());
}

void
openImage(std::string file)  // open image file with default viewer app
{
    system(std::string("start " + file).c_str());
}

bool
Viewer::init() {
    getInput(m_url, "host:port");
    if (!m_socket.init(100) || !m_socket.connect(m_url))
        return false;
    printf("Connection: OK\n");

    char cmd[] = "SUBSCRIBE";
    int len = m_socket.send(
        cmd,
        sizeof(
            cmd));  // this is special request for the server that identifies subscription requesst
    printf("Subscription: %s\n", len == sizeof(cmd) ? "OK" : "Fail");
    if (len != sizeof(cmd))
        return false;

    return true;
}

void
Viewer::run() {
    printf("Press ESC to type message\n");
    while (1) {
        int len = m_socket.recv();  // received new data from Server
        char* data = m_socket.data();

        if (len > 0) {
            std::cout << std::endl;
            m_console.clearScreen();  // clear screen
            for (std::string& str : split(data, "\n"))
                m_data.push_back(
                    str);  // append new message to the representation of server feed

            for (std::string str : m_data) {
                std::cout << str << std::endl << std::flush;
            }

            printf("----------\nPress ESC to type message\n");
        }
        if (m_console.isEscapePressed())  // pressing ESC activates typing mode
        {
            char message[256] = {};
            scanf("%255s", message);
        }
    }
}
