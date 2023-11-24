#ifndef MESSAGE_H
#define MESSAGE_H

#include <sstream>
#include <string>
#include <strstream>
#include <utility>

#include "MesType.h"
#include "Token.h"

class Message {
   public:
    MesType m_type;
    Token m_token;
    std::string m_fileName;
    std::string m_content;

    [[maybe_unused]] Message(MesType type, const Token& token,
                             std::string fileName, std::string content)
        : m_type(type),
          m_token(token),
          m_fileName(std::move(fileName)),
          m_content(std::move(content)) {}

    Message() {
        m_type = EMT;
        m_token = Token();
    }

    std::string serialize() {
        std::ostringstream  oss;
        if (m_type != EMT)
            oss << MesTypeToString[m_type] << " ";
        if (!m_token.isEmpty())
            oss << m_token.getToken() << " ";
        if (!m_fileName.empty())
            oss << m_fileName << " ";
        oss << m_content;
        return oss.str();
    }

    void deserialize(const std::string& str) {
        std::istringstream iss(str);
        std::string buff;
        iss >> buff;
        m_type = StringToMesType[buff];
        iss >> buff;
        m_token = Token(buff);
        if (m_type == FLE) {
            iss >> m_fileName;
        }
        iss >> m_content;
    }
};

#endif  //MESSAGE_H
