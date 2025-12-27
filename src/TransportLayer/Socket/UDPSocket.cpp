/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** UDPSocket
*/

#include "TransportLayer/Socket/UDPSocket.hpp"
#include <iostream>
#include <string.h>

ssize_t TransportLayer::UDPSocket::read(char *buffer, std::size_t size)
{
    sockaddr addr = {0};
    ssize_t nbyte = 0;

    _addrLen = sizeof(addr);
    nbyte = recvfrom(_socket, buffer, size, 0, &addr, &_addrLen);
    if (nbyte == -1)
    {
        _setSockState(SOCKERROR);
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
    memcpy(&_addr, &addr, _addrLen);
    return nbyte;
}

ssize_t TransportLayer::UDPSocket::readFrom(char *buffer, std::size_t size, sockaddr *addr, socklen_t *addrlen)
{
    ssize_t nbyte = recvfrom(_socket, buffer, size, 0, addr, addrlen);

    if (nbyte == -1)
    {
        _setSockState(SOCKERROR);
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
    return nbyte;
}

ssize_t TransportLayer::UDPSocket::write(const char *data, std::size_t size)
{
    sockaddr addr = {0};
    ssize_t nbyte = 0;

    memcpy(&addr, &_addr, _addrLen);
    nbyte = sendto(_socket, data, size, 0, &addr, _addrLen);
    if (nbyte == -1)
    {
        _setSockState(SOCKERROR);
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
    return nbyte;
}

ssize_t TransportLayer::UDPSocket::writeTo(const char *data, std::size_t size, sockaddr *addr, socklen_t addrlen)
{
    ssize_t nbyte = 0;

    nbyte = sendto(_socket, data, size, 0, addr, addrlen);
    if (nbyte == -1)
    {
        _setSockState(SOCKERROR);
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
    return nbyte;
}
