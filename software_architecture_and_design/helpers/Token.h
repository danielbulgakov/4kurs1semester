#ifndef TOKEN_H
#define TOKEN_H

#include <chrono>
#include <string>

class Token {
   private:
    std::string tokenString;
    bool isTimedOut;

    void create() {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        tokenString = std::to_string(now_time_t);
    }

   public:
    Token() { isTimedOut = false; }

    Token(const Token& t) {
        isTimedOut = t.isTimedOut;
        tokenString = t.tokenString;
    }

    explicit Token(const std::string& str) {
        isTimedOut = false;
        tokenString = str;
    }

    [[nodiscard]]
    bool isOutdated() const {
        return isTimedOut;
    }

    [[nodiscard]]
    bool isEmpty() const {
        return tokenString.empty();
    }

    [[maybe_unused]]
    void refresh() {
        isTimedOut = false;
        create();
    }

    std::string getToken() { return tokenString; }
};

#endif  //TOKEN_H
