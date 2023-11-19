#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include <ctime>
#include <sstream>

class Token {
public:
    explicit Token(bool createKey = true) {
        if (createKey) {
            m_key = generateKey();
        } else {
            m_key = "";
        }
    }

    Token(const std::string& str) { m_key = str; }

    std::string stringify() const { return m_key; }

    void destringify(const std::string& str) { m_key = str; }

    bool isEmpty() { return m_key.empty(); }
private:
    std::string m_key;

    static std::string generateKey() {
        std::ostringstream oss;
        oss << std::time(nullptr);
        return oss.str();
    }
};

#endif //TOKEN_H
