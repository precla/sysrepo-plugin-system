#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <optional>

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
     * @brief Clear Dns Server
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
     * @brief Get the list of DNS servers.
     * @return List of DNS servers.
     */
    static DnsServer::List getServers();
};

/**
 * @brief DnsSearchServer class
 */
class DnsSearchServer{

    private:
        std::string Domain;
        int Ifindex;
        int Search;
    public:
        /**
        * @brief Default constructor
        */
        DnsSearchServer();

        /**
        * @brief Constructor with all parameters
        */
        DnsSearchServer(std::string domain, int ifindex, int search);

        /**
        * @brief Clear DnsSearchServer
        */
        void clear();

        /**
        * @brief Set DnsSearchServer Domain
        */
        void setDomain(std::string domain);

        /**
        * @brief Set DnsSearchServer Ifindex
        */
        void setIfindex(int ifindex);

        /**
        * @brief Set DnsSearchServer search
        */
        void setSearch(int search);


        /**
        * @brief Get DnsSearchServer Domain
        */
        std::string getDomain();

        /**
        * @brief Get DnsSearchServer Ifindex
        */
        int getIfindex();

        /**
        * @brief Get DnsSearchServer Search
        */
        int getSearch();

        /**
        * @brief Overloaded == operator
        * @details It compares them by the Domain
        */
        bool operator==(const DnsSearchServer& other) const;

        /**
        * @brief Overloaded != operator
        * @details It compares them by the Domain
        */
        bool operator!=(const DnsSearchServer& other) const;

};

class DnsSearchServerList {

    private:
        /**
        * @brief Private Constructor forbids instantiating new object
        */
        DnsSearchServerList();

        /**
        * @brief Static DnsSearchServer vector
        */
        static std::vector<DnsSearchServer> servers;

    public:
        /**
        * @brief Clear DnsSearchServer list
        */
        void clearList();

        /**
        * @brief Add DnsSearchServer to the list
        */
        bool addDnsSearchServer(const DnsSearchServer& srv);

        /**
        * @brief Find DnsSearchServer by Name
        * @return std::optional<DnsSearchServer>
        * @details Returns std::nullopt if object is not found
        */
        std::optional<DnsSearchServer> findDnsSearchServer(const std::string& name);

        /**
        * @brief Remove DnsSearchServer
        * @param name of DnsSearchServer
        * @return true if removed, false otherwise
        */
        bool removeDnsSearchServer(const std::string& name);

        /**
        * @brief Compare DnsSearchServer
        * @param s1,s2 Compares 2 DnsSearchServers
        * @return true if are the same, false otherwise
        */
        bool compareDnsSearchServer(const DnsSearchServer& s1, const DnsSearchServer& s2);  
       

};

// /**
//  * @brief DNS search element type alias.
//  */
// using DnsSearch = std::string;

// /**
//  * @brief DNS search list type alias.
//  */
// using DnsSearchList = std::vector<DnsSearch>;

// /**
//  * @brief Get the list of DNS search domains.
//  * @return List of DNS search domains.
//  */
// DnsSearchList getSearchList();

}