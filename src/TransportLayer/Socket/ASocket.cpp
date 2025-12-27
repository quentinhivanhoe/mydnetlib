/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** ASocket
*/

#include "TransportLayer/Socket/ASocket.hpp"
#include <iostream>
#include <string.h>

using IOState = TransportLayer::IOState;

TransportLayer::ASocket::ASocket(int domain, int type, int protocol)
{
    _socket = socket(domain, type, protocol);

    if (_socket == INVALID_SOCKET_FD)
    {
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
}

TransportLayer::ASocket::~ASocket(void)
{
    if (_socket != INVALID_SOCKET_FD)
        this->close();
}

bool TransportLayer::ASocket::open(int domain, int type, int protocol)
{
    _socket = socket(domain, type, protocol);

    if (_socket == INVALID_SOCKET_FD)
    {
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
        return false;
    }
    return true;
}

bool TransportLayer::ASocket::close(void)
{
    if (_socket != INVALID_SOCKET_FD)
    {
        if (CLOSE(_socket) == -1)
        {
            std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
            _socket = INVALID_SOCKET_FD;
            return false;
        }
        _socket = INVALID_SOCKET_FD;
        return true;
    }
    return true;
}

bool TransportLayer::ASocket::bind(const struct sockaddr *addr, socklen_t addrlen) const
{
    if (!addr || !addrlen)
    {
        std::cerr << "error in parameters" << std::endl;
        return false;
    }
    if (::bind(_socket, addr, addrlen) == -1)
    {
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
        return false;
    }
    return true;
}

bool TransportLayer::ASocket::connect(const sockaddr *addr, socklen_t addrlen) const
{
    if (_socket != INVALID_SOCKET_FD)
    {
        if (::connect(_socket, addr, addrlen) == -1)
        {
            std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
            return false;
        }
        return true;
    }
    return false;
}

bool TransportLayer::ASocket::connect(std::string host, uint16_t port) const
{
    sockaddr_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port);
    if (!inet_aton(host.c_str(), &addr.sin_addr))
    {
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
        return false;
    }
    if (_socket != INVALID_SOCKET_FD)
    {
        if (::connect(_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == -1)
        {
            std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
            return false;
        }
        return true;
    }
    return false;
}

ssize_t TransportLayer::ASocket::read(char *buffer, std::size_t size)
{
    ssize_t nbyte = recv(_socket, buffer, size, 0);

    if (nbyte == -1)
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    return nbyte;
}

ssize_t TransportLayer::ASocket::write(const char *data, std::size_t size)
{
    ssize_t nbyte = send(_socket, data, size, 0);

    if (nbyte == -1)
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    return nbyte;
}

IOState TransportLayer::ASocket::getState(int timeoutSec, int timeoutUsec) const
{
    fd_set rfds = {0};
    fd_set wfds = {0};
    fd_set efds = {0};
    struct timeval timeout = {.tv_sec = timeoutSec, .tv_usec = timeoutUsec};

    FD_SET(_socket, &rfds);
    FD_SET(_socket, &wfds);
    FD_SET(_socket, &efds);

    switch (select(_socket + 1, &rfds, &wfds, &efds, &timeout))
    {
    case 0:
        return IOTIMEOUT;
    case -1:
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
        return IOERROR;
    default:
        if (FD_ISSET(_socket, &rfds))
            return IOREAD;
        if (FD_ISSET(_socket, &wfds))
            return IOWRITE;
        if (FD_ISSET(_socket, &efds))
            return IOEXCEPTION;
        return IOTIMEOUT;
    }
    return IOTIMEOUT;
}