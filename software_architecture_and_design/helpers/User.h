#ifndef USER_H
#define USER_H

#include <string>
#include <utility>
#include "Token.h"

enum Privelges {
    Default,
    Admin
};

class User {
public:
    User() = default;
    User(std::string login, std::string password, Privelges p) : m_login(std::move(login)), m_password(std::move(password)), m_priveleges(p)  {};

    std::string getLogin() { return m_login; }
    std::string getPassword() { return m_password; }
    Token getToken() { return m_token; }
    bool isMessageAcceptable(MType type) {
        if (type == MType::File && m_priveleges != Privelges::Admin) {
            return false;
        }
        return true;
    }
private:
    std::string m_login;
    std::string m_password;
    Token m_token;
    Privelges m_priveleges;
};

#endif //USER_H
