#include "TransportLayer/Socket/ASocket.hpp"
#include "TransportLayer/Socket/UDPSocket.hpp"
#ifndef _WIN32
#include <arpa/inet.h>
#endif
#include <iostream>
#include <string.h>
using namespace TransportLayer;

int main(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    UDPSocket socket;
    sockaddr_in addr;
    ssize_t nbyte = 0;
    char buffer[10] = {0};

    if (!socket.open(AF_INET, SOCK_DGRAM, 0))
    {
        std::cerr << "open methods don't works" << std::endl;
        return EXIT_FAILURE;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = ntohs(4242);

    if (!socket.bind(reinterpret_cast<sockaddr *>(&addr), sizeof(addr)))
    {
        std::cerr << "bind failed" << std::endl;
        return EXIT_FAILURE;
    }

    while (socket.getState(0, 0) == IOState::IOREAD)
        ;
    nbyte = socket.read(buffer, sizeof(buffer));

    if (nbyte == -1)
    {
        std::cerr << "read failed" << std::endl;
        return EXIT_FAILURE;
    }
    addr = socket.getSenderAddr();
    std::cout << "get message from: " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << "\n" << buffer << std::endl;

    if (socket.write(buffer, nbyte) == -1)
    {
        std::cerr << "write failed" << std::endl;
        return EXIT_FAILURE;
    }
    memset(buffer, 0, nbyte >= 0 ? nbyte : sizeof(buffer));
    while (socket.getState(0, 0) == IOState::IOREAD)
        ;
    socklen_t len = sizeof(addr);
    nbyte = socket.readFrom(buffer, sizeof(buffer), reinterpret_cast<sockaddr *>(&addr), &len);

    if (nbyte == -1)
    {
        std::cerr << "read failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "get message from: " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << "\n" << buffer << std::endl;

    if (socket.writeTo(buffer, nbyte, reinterpret_cast<sockaddr *>(&addr), len) == -1)
    {
        std::cerr << "write failed" << std::endl;
        return EXIT_FAILURE;
    }
    if(!socket.close())
    {
        std::cerr << "close failed" << std::endl;
        return EXIT_FAILURE;
    }
#ifdef _WIN32
    WSACleanup();
#endif
    return EXIT_SUCCESS;
}
