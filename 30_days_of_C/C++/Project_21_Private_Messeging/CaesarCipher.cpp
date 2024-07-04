#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(int shift) : shift(shift % 26) {}

std::string CaesarCipher::encrypt(const std::string& text) {
    std::string result;
    for (char c : text) {
        result += shiftChar(c, shift);
    }
    return result;
}

std::string CaesarCipher::decrypt(const std::string& text) {
    std::string result;
    for (char c : text) {
        result += shiftChar(c, -shift);
    }
    return result;
}

char CaesarCipher::shiftChar(char c, int shift) {
    if (std::isalpha(c)) {
        char base = std::isupper(c) ? 'A' : 'a';
        return static_cast<char>(base + (c - base + shift + 26) % 26);
    }
    return c;
}
