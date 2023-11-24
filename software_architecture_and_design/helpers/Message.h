#ifndef MESSAGE_H
#define MESSAGE_H

#include <optional>
#include <sstream>
#include <string>
#include <vector>

// Type of messages
enum MessageType { SIMPLE, FILE_TRANSFER, SYSTEM };

// Message class
class Message {
   public:
    MessageType type;
    std::optional<std::string> token;     // Optional parameter
    std::optional<std::string> fileName;  // Optional parameter
    std::string content;

    // Simple message constructor
    Message(MessageType t, const std::string& tk, const std::string& msg) : type(t), token(tk), content(msg) {}

    // File message constructor
    Message(MessageType t, const std::string& tk, const std::string& file, std::string data)
        : type(t), token(tk), fileName(file), content(std::move(data)) {}

    // System message constructor
    Message(MessageType t, const std::string& msg) : type(t), content(msg) {}

    static std::string serialize(const Message& msg) {
        std::stringstream ss;

        ss << "type: " << msg.type << "\n";

        if (msg.token.has_value()) {
            ss << "token: " << msg.token.value() << "\n";
        }

        if (msg.type == FILE_TRANSFER) {
            if (msg.fileName.has_value()) {
                ss << "fileName: " << msg.fileName.value() << "\n";
            }
            ss << "content: " << msg.content;
        } else {
            ss << "content: " << msg.content;
        }

        return ss.str();
    }

    static Message deserialize(const std::string& data) {
        Message msg(SIMPLE, "", "");

        std::stringstream ss(data);
        std::string line;

        while (std::getline(ss, line)) {
            size_t pos = line.find(": ");
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 2);

                if (key == "type") {
                    msg.type = static_cast<MessageType>(std::stoi(value));
                } else if (key == "token") {
                    msg.token = value;
                } else if (key == "fileName") {
                    msg.fileName = value;

                    pos = data.find("content: ") + 9;
                    msg.content = data.substr(pos);
                    break;
                } else if (key == "content") {
                    msg.content = value;
                }
            }
        }

        return msg;
    }
};

#endif  //MESSAGE_H
