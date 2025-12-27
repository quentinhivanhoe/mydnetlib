/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** TCPSocket
*/

#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_
#include "ASocket.hpp"

namespace TransportLayer
{
class TCPSocket : public ASocket
{
  public:
    /**
     * @brief Create a TCP socket
     *
     */
    TCPSocket() : ASocket(AF_INET, SOCK_STREAM, 0) {};

    /**
     * @brief Create a TCP socket from an external fd
     *
     * @param sockfd the external fd
     */
    inline TCPSocket(socket_t sockfd)
    {
        _socket = sockfd;
    };

    /**
     * @brief Create a TCP socket from antoher TCP socket
     * it will close the second TCP socket
     * @param other Another TCP socket
     */
    TCPSocket(TCPSocket &other);

    /**
     * @brief Overload the assignment operator
     * to create a new TCP socket from a fd
     *
     * @param sockfd External fd
     */
    TCPSocket &operator=(socket_t sockfd);

    /**
     * @brief Overload assignment operator
     * to create a TCP socket from another TCP socket
     *
     * @param other
     * @return TCPSocket
     */
    TCPSocket &operator=(TCPSocket other);

    /**
     * @brief Close the fd of the TCP socket
     *
     */
    ~TCPSocket() = default;

    /**
     * @brief Set as a passive socket to accept incoming connection
     *
     * @param backlog Number of connection accepted
     * @return true set as passive socket sucessfully
     * @return false error happen
     */
    bool listen(int backlog);

    /**
     * @brief Accept a new connection, don't store his address
     *
     * @return socket_t New connection socket
     */
    socket_t accept(void);

    /**
     * @brief Aceept a new connection
     * and store his address and his address size in `addr` and `addrlen`
     *
     * @param addr New connection address
     * @param addrlen New connection address size
     * @return socket_t New connection socket
     */
    socket_t accept(sockaddr *addr, socklen_t *addrlen);

  protected:
  private:
};

} // namespace TransportLayer

#endif /* !TCPSOCKET_HPP_ */
