/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** ISocket
*/

#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_
#ifdef _WIN32
// Windows library
#include <cstdint>
#include <winsock2.h>
#include <ws2tcpip.h>

// Windows special socket define
#define CLOSE(s) closocket(s)
#define SOCKET_ERROR_CODE WSAGetLastError()
#define INVALID_SOCKET_FD INVALID_SOCKET

// Windows special type
typedef SOCKET socket_t;
#else
// Linux library
#include <cstdint>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

// Linux special socket define
#define CLOSE(s) close(s)
#define SOCKET_ERROR_CODE errno
#define INVALID_SOCKET_FD -1

// Linux socket type
typedef int socket_t;
#endif

namespace Network::TransportLayer
{

/**
 * @enum IOState
 * @brief Represent socket state
 *
 */
enum IOState
{
    IOREAD,   // there is data to read
    IOWRITE,  // socket is writable
    IOERROR,  // error happened
    IOTIMEOUT // no event happened
};

/**
 * @class ISocket
 * @brief Interface for socket abstraction
 *
 */
class ISocket
{
  public:
    /**
     * @brief Destroy the ISocket object
     *
     */
    virtual ~ISocket() = default;

    /**
     * @brief get internal socket
     *
     * @return socket_t internal socket
     */
    inline virtual socket_t getSocket() const = 0;

    /**
     * @brief close the internal socket
     *
     * @return bool true if ther is no error false if an error happen
     */
    virtual bool close() = 0;

    /**
     * @brief read bytes from the socket
     *
     * @param buffer store socket data ito it
     * @param size buffer's size
     * @return ssize_t bytes readed, -1 on error
     */
    virtual ssize_t read(char *buffer, std::size_t size) const = 0;

    /**
     * @brief
     *
     * @param data data to write on the socket
     * @param size data size
     * @return bytes write, -1 on error
     */
    virtual ssize_t write(const char *data, std::size_t size) const = 0;

    /**
     * @brief get current state of the socket
     *
     * @param timeoutSec time in second before timeout
     * @param timeoutUsec time in millisecond before timeout
     * @return IOState current socket state
     */
    virtual IOState getState(int timeoutSec, int timeoutUsec) const = 0;

  protected:
  private:
};

} // namespace Network::TransportLayer

#endif /* !ISOCKET_HPP_ */
