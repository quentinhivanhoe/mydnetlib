/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** TCPSocket
*/

#include "TransportLayer/Socket/TCPSocket.hpp"
#include <iostream>
#include <string.h>

TransportLayer::TCPSocket::TCPSocket(TCPSocket &other)
{
    if (_socket != INVALID_SOCKET_FD)
        this->close();
    _socket = other._socket;
    _setSockState(other.getSockState());
    other._socket = INVALID_SOCKET_FD;
    other._setSockState(SOCKINVALID);
}

TransportLayer::TCPSocket &TransportLayer::TCPSocket::operator=(socket_t sockfd)
{
    if (_socket != INVALID_SOCKET_FD)
        this->close();
    _socket = sockfd;
    _setSockState(SOCKCONNECTED);
    return *this;
}

TransportLayer::TCPSocket &TransportLayer::TCPSocket::operator=(TCPSocket other)
{
    if (_socket != INVALID_SOCKET_FD)
        this->close();
    _socket = other._socket;
    _setSockState(other.getSockState());
    other.close();
    return *this;
}

bool TransportLayer::TCPSocket::listen(int backlog)
{
    if (::listen(_socket, backlog) == -1)
    {
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
        _setSockState(SOCKERROR);
        return false;
    }
    _setSockState(SOCKLISTENING);
    return true;
}

socket_t TransportLayer::TCPSocket::accept(void)
{
    sockaddr addr = {0};
    socklen_t addrlen = sizeof(addr);
    socket_t sock = ::accept(_socket, &addr, &addrlen);

    if (sock == INVALID_SOCKET_FD)
    {
        _setSockState(SOCKERROR);
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
    return sock;
}

socket_t TransportLayer::TCPSocket::accept(sockaddr *addr, socklen_t *addrlen)
{
    socket_t sock = ::accept(_socket, addr, addrlen);

    if (sock == INVALID_SOCKET_FD)
    {
        _setSockState(SOCKERROR);
        std::cerr << strerror(SOCKET_ERROR_CODE) << std::endl;
    }
    return sock;
}