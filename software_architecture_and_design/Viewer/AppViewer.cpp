#define _CRT_SECURE_NO_WARNINGS
#include "AppViewer.h"
#include <map>
#include "../helpers/Message.h"
#include "../helpers/UtilFile.h"
#include "../helpers/UtilString.h"
#include "helpers/Socket.h"

// get some input string from user and store it in a variable
void
getInput(char* param, const char* name) {
    printf("Enter %s or press ENTER to use saved value (\"%s\")\n", name, param);
    char buf[256] = {};
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        char val[256] = {};
        sscanf(buf, "%s\r\n", val);
        memcpy(param, val, 256);
    }
}

// run application, possibly with arguments. Example: runApp("AppServer.exe 12345");
void
runApp(const std::string& cmd) {
    system(cmd.c_str());
}

void
openImage(const std::string& file)  // open image file with default viewer app
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

[[noreturn]]
void
Viewer::run() {
    printf("Press ESC to type message\n");
    char message[256] = {};
    char meta[256] = {};
    while (true) {
        int len = m_socket.recv();  // received new data from Server
        char* data = m_socket.data();

        if (len > 0) {
            m_console.clearScreen();  // clear screen
            for (std::string& str : split(data, "\n"))
                m_data.push_back(str);  // append new message to the representation of server feed

            for (const std::string& str : m_data)
                printf("%s\n", str.c_str());  // display entire feed
            printf("----------\nPress ESC to type message\n");
        }
        if (m_console.isEscapePressed() || m_console.isEnterPressed())  // pressing ESC activates typing mode
        {
            fgets(message, 256, stdin);
            Message m;
            if (!isLogedIn) {
                m = Message(SYS, m_token, std::string(), std::string(message));
            } else {
                if (fileExists(message)) {
                    m = Message(FLE, m_token, std::filesystem::path(message).filename().string(),
                                getFileStr(message));
                } else {
                    m = Message(MS, m_token, std::string(),message);
                }
            }
            m_socket.sendStr(m.serialize());
        }
        if (message[0] != '\0') {
            message[0] = '\0';
            meta[0] = '\0';
        }
    }
}
