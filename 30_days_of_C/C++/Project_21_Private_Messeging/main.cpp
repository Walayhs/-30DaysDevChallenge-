#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include "CaesarCipher.h"

using asio::ip::tcp;

const int PORT = 12345;

void client(const std::string& host, int shift) {
    try {
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, std::to_string(PORT));
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        CaesarCipher cipher(shift);

        std::string message;
        while (true) {
            std::cout << "Enter message: ";
            std::getline(std::cin, message);

            std::string encryptedMessage = cipher.encrypt(message);
            std::cout << "Encrypted (developer view): " << encryptedMessage << std::endl;

            asio::write(socket, asio::buffer(encryptedMessage));

            char reply[1024];
            size_t reply_length = asio::read(socket, asio::buffer(reply, encryptedMessage.size()));
            std::string decryptedMessage = cipher.decrypt(std::string(reply, reply_length));
            std::cout << "Server: " << decryptedMessage << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void server(int shift) {
    try {
        asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        CaesarCipher cipher(shift);

        while (true) {
            char data[1024];
            size_t length = socket.read_some(asio::buffer(data));

            std::string encryptedMessage(data, length);
            std::cout << "Encrypted (developer view): " << encryptedMessage << std::endl;

            std::string message = cipher.decrypt(encryptedMessage);
            std::cout << "Client: " << message << std::endl;

            std::string reply = cipher.encrypt(message);
            asio::write(socket, asio::buffer(reply));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int main() {
    int shift;
    std::string mode;

    std::cout << "Enter shift value: ";
    std::cin >> shift;
    std::cout << "Enter mode (server/client): ";
    std::cin >> mode;
    std::cin.ignore();  // Clear the input buffer

    if (mode == "server") {
        server(shift);
    } else if (mode == "client") {
        std::string host;
        std::cout << "Enter server IP: ";
        std::cin >> host;
        std::cin.ignore();  // Clear the input buffer
        client(host, shift);
    } else {
        std::cerr << "Invalid mode!" << std::endl;
    }

    return 0;
}
