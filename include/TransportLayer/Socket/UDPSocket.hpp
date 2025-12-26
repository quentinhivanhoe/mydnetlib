/*
** EPITECH PROJECT, 2025
** mydnetlib
** File description:
** UDPSocket
*/

#ifndef UDPSOCKET_HPP_
#define UDPSOCKET_HPP_
#include "ASocket.hpp"

namespace TransportLayer
{
class UDPSocket : public ASocket
{
  public:
    /**
     * @brief Create an UDP socket with IPV4 address
     *
     */
    UDPSocket(void) : ASocket(AF_INET, SOCK_DGRAM, 0) {};

    /**
     * @brief Destroy the UDPSocket object
     *
     */
    ~UDPSocket() = default;

    /**
     * @brief read bytes from the socket and store the sender addr
     *
     * @param buffer store socket data into it
     * @param size buffer's size
     * @return ssize_t bytes readed, -1 on error
     */
    ssize_t read(char *buffer, std::size_t size) override;

    /**
     * @brief same as read but don't store sender address internally but in addr
     *
     * @param buffer buffer to store data
     * @param size size of the buffer
     * @param addr address to store sender address
     * @param addrlen len of the sender address
     * @return ssize_t number of byte read
     */
    ssize_t readFrom(char *buffer, std::size_t size, sockaddr *addr, socklen_t *addrlen);

    /**
     * @brief write data throught to the last data sender
     *
     * @param data data to write on the socket
     * @param size data size
     * @return bytes write, -1 on error
     */
    ssize_t write(const char *data, std::size_t size) override;

    /**
     * @brief write data throught to the address in addr
     *
     * @param data data to write
     * @param size size of the data
     * @param addr destination address
     * @param addrlen size of the destination address
     * @return ssize_t number of byte write
     */
    ssize_t writeTo(const char *data, std::size_t size, sockaddr *addr, socklen_t addrlen);

    /**
     * @brief Get the last sender address
     *
     * @return sockaddr_in sender address
     */
    inline sockaddr_in getSenderAddr(void)
    {
        return _addr;
    }

  protected:
  private:
    sockaddr_in _addr;
    socklen_t _addrLen;
};

} // namespace TransportLayer

#endif /* !UDPSOCKET_HPP_ */
