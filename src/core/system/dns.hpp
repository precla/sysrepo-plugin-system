#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace ietf::sys::dns {

/**
 * @brief DNS server.
 */
class DnsServer {
    private:
        std::string Name; ///< Arbitrary name of the DNS server.
        std::string Address; ///< Address of the DNS server.
        std::uint16_t Port; ///< Port of the DNS server.

        using List = std::vector<DnsServer>;

    public:


    /**
     * @brief Default constructor.
     */
    DnsServer();

    /**
     * @brief Constructor with all params.
     */
    DnsServer(std::string name, std::string address, std::uint16_t port);

    /**
     * @brief Clear Dns Server, set port to 53, address NULL and port 0
     */
    void clear();

    /**
     * @brief Set Name of Dns Server
     */
    void setName(const std::string name);

    /**
     * @brief Set Address of Dns Server
     */
    void setAddress(const std::string address);

    /**
     * @brief Set Address of Dns Server
     */
    void setPort(const std::uint16_t port);

    /**
     * @brief Get Name of Dns Server
     */
    std::string getName();

    /**
     * @brief Get Address of Dns Server
     */
    std::string getAddress();

    /**
     * @brief Get Port of Dns Server
     */
    std::uint16_t getPort();

    /**
     * @brief Destruct DnsServer object
     */
    void close();


    /**
     * @brief Get the list of DNS servers.
     * @return List of DNS servers.
     */
    static DnsServer::List getServers();
};

/**
 * @brief DNS search element type alias.
 */
using DnsSearch = std::string;

/**
 * @brief DNS search list type alias.
 */
using DnsSearchList = std::vector<DnsSearch>;

/**
 * @brief Get the list of DNS search domains.
 * @return List of DNS search domains.
 */
DnsSearchList getSearchList();

}