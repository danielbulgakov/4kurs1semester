#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

enum PrivilegeLevel { NORMAL, ADMIN };

class User {
   private:
    std::string login;
    std::string password;
    PrivilegeLevel privilegeLevel;

   public:
    User() = default;

    // Constructor
    User(const std::string& login, const std::string& password, PrivilegeLevel privilegeLevel)
        : login(login), password(password), privilegeLevel(privilegeLevel) {}

    // Getter methods
    std::string getLogin() const { return login; }

    void setPassword(std::string newPassword) { password = newPassword; }

    std::string getPassword() const { return password; }

    PrivilegeLevel getPrivilegeLevel() const { return privilegeLevel; }

    bool authenticate(const std::string& providedPassword) const { return password == providedPassword; }
};

#endif  //USER_H
