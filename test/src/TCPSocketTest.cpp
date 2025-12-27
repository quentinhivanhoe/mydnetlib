/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** TCPSocketTest
*/
#include "TransportLayer/Socket/TCPSocket.hpp"
#include <iostream>
using namespace TransportLayer;

static bool init_socket(void)
{
    TCPSocket socket;
    bool res = false;

    if (socket.getSocket() != INVALID_SOCKET_FD)
        res = true;
    socket.close();
    return res;
}

static bool copy_contructor_fd(void)
{
    TCPSocket socket(::socket(AF_INET, SOCK_STREAM, 0));
    bool res = false;

    if (socket.getSocket() != INVALID_SOCKET_FD)
        res = true;
    socket.close();
    return res;
}

static bool copy_constructor_socket(void)
{
    TCPSocket s1;
    TCPSocket s2(s1);
    bool res = false;

    if (s1.getSocket() == INVALID_SOCKET_FD && s2.getSocket() != INVALID_SOCKET_FD)
        res = true;
    s2.close();
    return res;
}

static bool assignment_operator_fd(void)
{
    socket_t sockfd = (socket_t)::socket(AF_INET, SOCK_STREAM, 0);
    TCPSocket socket = sockfd;
    bool res = false;

    if (socket.getSocket() == sockfd)
        res = true;
    socket.close();
    return res;
}

static bool assignment_operator_socket(void)
{
    TCPSocket s1;
    TCPSocket s2 = s1;
    bool res = false;

    if (s1.getSocket() == INVALID_SOCKET_FD && s2.getSocket() != INVALID_SOCKET_FD)
        res = true;
    s2.close();
    return res;
}

size_t tcp_test_main(size_t *test_passed)
{
    bool (*test_func[])(void) = {&init_socket,
                                 &copy_contructor_fd,
                                 &copy_constructor_socket,
                                 &assignment_operator_fd,
                                 &assignment_operator_socket,
                                 NULL};
    size_t i = 0;

    for (; test_func[i]; i++)
        if (test_func[i]())
            (*test_passed)++;
    return i;
}