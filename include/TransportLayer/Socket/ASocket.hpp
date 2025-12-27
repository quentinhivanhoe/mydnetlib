/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** Asocket
*/

#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_
#include "ISocket.hpp"
namespace TransportLayer
{
class ASocket : public ISocket
{
  public:
    /**
     * @brief Set the to INVALID_SOCKET_FD
     * you need to set the socket
     *
     */
    ASocket(void) : _socket(INVALID_SOCKET_FD) {};

    /**
     * @brief Create a new socket
     *
     * @param domain    communication domain
     * @param type      communication semantics
     * @param protocol  particular protocol applied to the socket
     */
    ASocket(int domain, int type, int protocol);

    /**
     * @brief Close the socket
     *
     */
    ~ASocket();

    /**
     * @brief Create a new socket
     *
     * @param domain    communication domain
     * @param type      communication semantics
     * @param protocol  socket protocol
     * @return true     socket is succesfully open
     * @return false    error happened
     */
    bool open(int domain, int type, int protocol) override;

    /**
     * @brief close the internal socket
     *
     * @return bool true if ther is no error false if an error happen
     */
    bool close(void) override;

    /**
     * @brief assigns the address specified by addr to the socket referredto by
     * the file descriptor sockfd
     *
     * @param addr address to assign
     * @param addrlen the address structure len in byte
     * @return true assign address sucessfully
     * @return false error happen
     */
    bool bind(const struct sockaddr *addr, socklen_t addrlen) const override;

    /**
     * @brief Get the socket fd
     *
     * @return socket_t internal socket
     */
    inline socket_t getSocket(void) const override
    {
        return _socket;
    }

    /**
     * @brief read bytes from the socket
     *
     * @param buffer store socket data ito it
     * @param size buffer's size
     * @return ssize_t bytes readed, -1 on error
     */
    virtual ssize_t read(char *buffer, std::size_t size) override;

    /**
     * @brief write data throught the socket
     *
     * @param data data to write on the socket
     * @param size data size
     * @return bytes write, -1 on error
     */
    virtual ssize_t write(const char *data, std::size_t size) override;

    /**
     * @brief get current state of the socket
     *
     * @param timeoutSec time in second before timeout
     * @param timeoutUsec time in millisecond before timeout
     * @return IOState current socket state
     */
    IOState getState(int timeoutSec, int timeoutUsec) const override;

  protected:
    socket_t _socket; // File descriptor representing the socket

  private:
};
} // namespace TransportLayer

#endif /* !ASOCKET_HPP_ */
