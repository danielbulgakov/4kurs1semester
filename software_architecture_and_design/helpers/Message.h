#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <sstream>
#include <utility>
#include <utility>
#include "Token.h"
#include "MType.h"

class Message {
public:
    Message() = default;
    Message(MType type, Token token, std::string content);
    Message(MType type, Token token, std::string filename, std::string content);

    void setType(MType type) { m_type = type; };
    void setToken(Token token) { m_token = std::move(token); };
    void setFileName(std::string filename) { m_filename = std::move(filename); };
    void setContent(std::string content) { m_content = std::move(content); };

    MType getType() { return m_type; }
    Token getToken() { return m_token; }
    std::string getFileName() { return m_filename; }
    std::string getContent() { return m_content; }

    std::string stringify() const;
    void destringify(const std::string& str);
private:
    MType m_type;
    Token m_token;
    std::string m_filename;
    std::string m_content;
};

std::string Message::stringify() const {
    std::string msg;

    switch (m_type) {
        case MType::File : {
            msg.append("FLE");
            msg.append(" ");
            msg.append(m_filename);
            msg.append(" ");
            msg.append(m_content);
            msg.append(" ");
            msg.append(m_token.stringify());
            break;
        };
        case MType::Msg : {
            msg.append("MSG");
            msg.append(" ");
            msg.append(m_content);
            msg.append(" ");
            msg.append(m_token.stringify());
            break;
        };
        case MType::System : {
            msg.append("SYS");
            msg.append(" ");
            msg.append(m_content);
            msg.append(" ");
            msg.append(m_token.stringify());
            break;
        };
    }


    return msg;
}

void Message::destringify(const std::string& str) {
    std::istringstream iss(str);
    std::string type;
    iss >> type;

    if (type == "FLE") {
        m_type = MType::File;
        iss >> m_filename;
    } else if (type == "MSG") {
        m_type = MType::Msg;
    } else if (type == "SYS") {
        m_type = MType::System;
    }

    iss >> m_content;

    std::string tokenStr;
    iss >> tokenStr;
    m_token.destringify(tokenStr);
}

Message::Message(MType type, Token token, std::string filename, std::string content) {
    m_type = type;
    m_token = std::move(token);
    m_filename = std::move(filename);
    m_content = std::move(content);
}

Message::Message(MType type, Token token, std::string content) {
    m_type = type;
    m_token = std::move(token);
    m_filename = std::string();
    m_content = std::move(content);
}

#endif //MESSAGE_H
