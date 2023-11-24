#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>

#include <map>
#include <string>

class Database {
   public:
    enum Privilege {
        USER,
        ADMIN,
        SUPER_ADMIN
    };

    struct User {
        std::string login;
        std::string password;
        std::string id;
        Privilege privilege;
    };

    void addUser(const User& user) {
        users[user.login] = user;
    }

    bool validateUser(const std::string& login, const std::string& password) {
        auto it = users.find(login);
        if (it != users.end()) {
            return it->second.password == password;
        }
        return false;
    }

    std::string getUserId(const std::string& login) {
        auto it = users.find(login);
        if (it != users.end()) {
            return it->second.id;
        }
        return "";
    }

    Privilege getUserPrivilege(const std::string& login) {
        auto it = users.find(login);
        if (it != users.end()) {
            return it->second.privilege;
        }
        return USER; // default privilege
    }

   private:
    std::map<std::string, User> users;
};

#endif  //DATABASE_H
