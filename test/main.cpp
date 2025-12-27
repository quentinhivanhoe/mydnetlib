/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** main
*/

#include "test.hpp"
#include "TransportLayer/Socket/ISocket.hpp"

int main(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    size_t test_passed = 0;
    size_t nb_test = 0;

    nb_test += tcp_test_main(&test_passed);

    std::cout << test_passed << "/" << nb_test << std::endl;
#ifdef _WIN32
    WSACleanup();
#endif
}