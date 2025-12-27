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

static bool server(void)
{
    TCPSocket s1;
    sockaddr_in addr = {0};
    socklen_t addrlen = sizeof(addr);
    TCPSocket s2;
    char buffer[13] = {0};

    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(4242);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (s1.getSocket() == INVALID_SOCKET_FD)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    if (!s1.bind(reinterpret_cast<sockaddr *>(&addr), sizeof(addr)))
    {
        std::cerr << "Bind failed !" << std::endl;
        return false;
    }

    if (!s1.listen(10))
    {
        std::cerr << "Listen failed" << std::endl;
        return false;
    }

    std::cout << "Server listening on localhost and port 4242" << std::endl;
    s2 = s1.accept(reinterpret_cast<sockaddr *>(&addr), &addrlen);
    if (s2.getSocket() == INVALID_SOCKET_FD)
    {
        std::cerr << "Accept failed" << std::endl;
        return false;
    }

    if (s2.read(buffer, sizeof(buffer)) == -1)
    {
        std::cerr << "Read failed" << std::endl;
        return false;
    }
    std::cout << "Client[" << s2.getSocket() << "] says:" << buffer << std::endl;

    if (s2.write("Hello client", 13) == -1)
    {
        std::cerr << "Write failed" << std::endl;
        return false;
    }
    return true;
}

static bool client(void)
{
    TCPSocket socket;
    sockaddr_in addr = {0};
    socklen_t addrlen = sizeof(addr);
    char buffer[14] = {0};

    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(4242);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (socket.getSocket() == INVALID_SOCKET_FD)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    if (!socket.connect(reinterpret_cast<sockaddr *>(&addr), addrlen))
    {
        std::cerr << "Connect failed" << std::endl;
        return false;
    }

    if (socket.write("Hello server", 13) == -1)
    {
        std::cerr << "Write failed" << std::endl;
        return false;
    }

    if (socket.read(buffer, sizeof(buffer)) == -1)
    {
        std::cerr << "Read failed" << std::endl;
        return false;
    }

    std::cout << "Server says: " << buffer << std::endl;
    return true;
}

size_t tcp_test_main(size_t *test_passed)
{
    // bool (*test_func[])(void) = {&init_socket,
    //                              &copy_contructor_fd,
    //                              &copy_constructor_socket,
    //                              &assignment_operator_fd,
    //                              &assignment_operator_socket,
    //                              NULL};
    // size_t i = 0;

    // for (; test_func[i]; i++)
    //     if (test_func[i]())
    //         (*test_passed)++;
    // return i;
    if (client())
        (*test_passed)++;
    return 1;
}