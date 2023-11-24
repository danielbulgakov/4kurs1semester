#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <chrono>
#include <map>
#include <string>
#include "User.h"

class UserDatabase {
   private:
    std::map<std::string, User> users;

   public:
    bool addUser(const std::string& login, const std::string& password, PrivilegeLevel privilegeLevel, std::string token = std::string()) {
        if (token.empty()) {
            auto now = std::chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
            token = std::to_string(seconds.count());
        }
        // Check if the token already exists
        if (users.find(token) == users.end()) {
            users[token] = User(login, password, privilegeLevel);
            return true; // User added successfully
        }
        return false; // Token already exists
    }

    bool authenticateUser(const std::string& token, const std::string& providedPassword) {
        auto it = users.find(token);
        if (it != users.end()) {
            return it->second.authenticate(providedPassword);
        }
        return false; // Token not found
    }

    bool doesTokenExist(const std::string& token) const {
        return users.find(token) != users.end();
    }

    std::string getTokenByLogin(const std::string& login) const {
        for (const auto& pair : users) {
            if (pair.second.getLogin() == login) {
                return pair.first;
            }
        }
        return std::string();
    }

    PrivilegeLevel getPrivilegeLevel(const std::string& token) const {
        auto it = users.find(token);
        if (it != users.end()) {
            return it->second.getPrivilegeLevel();
        }
        // Return a default value or handle the case where the token doesn't exist
        return NORMAL;
    }

    std::string getLogin(const std::string& token) const {
        auto it = users.find(token);
        if (it != users.end()) {
            return it->second.getLogin();
        }
        // Return a default value or handle the case where the token doesn't exist
        return "";
    }

};

#endif  //USERDATABASE_H
