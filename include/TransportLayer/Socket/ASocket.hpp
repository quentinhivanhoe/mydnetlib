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
    ASocket(void) : _socket(INVALID_SOCKET_FD), _state(SOCKINVALID) {};

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
    bool bind(const struct sockaddr *addr, socklen_t addrlen) override;

    /**
     * @brief Connect to another socket moste needed in TCP socket but for UDP socket
     * a writeTo connect to the socket implicitely
     *
     * @param addr Address to connect
     * @param addrlen Size of the address in byte
     * @return true connect sucessfully
     * @return false error happen
     */
    bool connect(const sockaddr *addr, socklen_t addrlen) override;

    /**
     * @brief Connect to another socket moste needed in TCP socket but for UDP socket
     * a writeTo connect to the socket implicitely
     *
     * @param host host as human readable (127.0.0.1)
     * @param port port to connet on the host machine
     * @return true connect sucessfully
     * @return false error happen
     */
    bool connect(const char *host, uint16_t port) override;

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

    /**
     * @brief Get the internal socket state
     *
     * @return SockState internal socket state
     */
    inline SockState getSockState(void) const override
    {
      return _state;
    };

  protected:
    socket_t _socket; // File descriptor representing the socket

    /**
     * @brief Set the internal socket state
     *
     * @param state internal socket state
     */
    inline void _setSockState(SockState state)
    {
        _state = state;
    };

  private:
    SockState _state; //
};
} // namespace TransportLayer

#endif /* !ASOCKET_HPP_ */
