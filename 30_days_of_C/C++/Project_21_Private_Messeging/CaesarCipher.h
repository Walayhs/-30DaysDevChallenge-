#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <string>

class CaesarCipher {
public:
    explicit CaesarCipher(int shift);
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);

private:
    int shift;
    char shiftChar(char c, int shift);
};

#endif // CAESARCIPHER_H
