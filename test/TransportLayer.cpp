#include "TransportLayer/Socket/ASocket.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
using namespace TransportLayer;

int main(void)
{
    ASocket socket;
    sockaddr_in addr;
    char buffer[10] = {0};

    if (!socket.open(AF_INET, SOCK_DGRAM, 0))
    {
        std::cerr << "open methods don't works" << std::endl;
        return EXIT_FAILURE;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = ntohs(4242);

    if (bind(socket.getSocket(), reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
    {
        std::cerr << "bind failed" << std::endl;
        return EXIT_FAILURE;
    }

    while (socket.getState(0, 0) == IOState::IOREAD);
    ssize_t nbyte = socket.read(buffer, sizeof(buffer));

    if (nbyte == -1)
    {
        std::cerr << "read failed" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << buffer << std::endl;

    if (socket.write(buffer, nbyte) == -1)
    {
        std::cerr << "write failed" << std::endl;
        return EXIT_FAILURE;
    }
    memset(buffer, 0, nbyte >= 0 ? nbyte : sizeof(buffer));
    return EXIT_SUCCESS;
}
