#include "dns.hpp"
#include "sdbus-c++/Message.h"
#include <sdbus-c++/sdbus-c++.h>

namespace ietf::sys::dns {


DnsServer::DnsServer()
    : Port(53){}


DnsServer::DnsServer(std::string name, std::string address, std::uint16_t port = 53)
    : Name{name},
      Address{address},
      Port{port} {}

void DnsServer::clear(){
    this->Address.clear();
    this->Port = 0;
    this->Name.clear(); 
}

void DnsServer::setName(const std::string name){
    this->Name = name;
}

void DnsServer::setPort(const std::uint16_t port){
    this->Port = port;
}

void DnsServer::setAddress(const std::string address){
    this->Address = address;
}

std::string DnsServer::getName(){
    return Name;
}

std::uint16_t DnsServer::getPort(){
    return Port;
}

std::string DnsServer::getAddress(){
    return Address;
}

DnsSearchServer::DnsSearchServer() 
    :   Ifindex{0},
        Search{0}{
        Domain.clear();
    }

DnsSearchServer::DnsSearchServer(std::string domain, int ifindex, int search):
    Domain{domain},
    Ifindex{ifindex},
    Search{search}
    {};

std::string DnsSearchServer::getDomain(){
    return Domain;
}

int DnsSearchServer::getIfindex(){
    return Ifindex;
}

int DnsSearchServer::getSearch(){
    return Search;
}

void DnsSearchServer::setDomain(std::string domain){
    this->Domain = domain;
}

void DnsSearchServer::setIfindex(int ifindex){
    this->Ifindex = ifindex;
}

void DnsSearchServer::setSearch(int search){
    this->Search = search;
}

bool DnsSearchServer::operator==(const DnsSearchServer& other) const {
    return (this->Domain == other.Domain);
}

bool DnsSearchServer::operator!=(const DnsSearchServer& other) const {
    return (this->Domain == other.Domain);
}

// DnsSearchServerList implementation

std::vector<DnsSearchServer> DnsSearchServerList::servers;

void DnsSearchServerList::clearList(){
    servers.clear();
}

bool DnsSearchServerList::addDnsSearchServer(const DnsSearchServer& srv){
    for (DnsSearchServer& server : servers){
        if(server == srv){
            //already exists
            return false;
        }
    }

    servers.push_back(srv);
    return true;
}

std::optional<DnsSearchServer> DnsSearchServerList::findDnsSearchServer(const std::string& name){

    for(DnsSearchServer& server : servers){
        if(server.getDomain() == name){
            return server;
        }
    }
    
    return std::nullopt;
}

bool DnsSearchServerList::removeDnsSearchServer(const std::string& name){

    std::vector<DnsSearchServer>::iterator it = servers.begin();

    for(it; it != servers.end(); it++){
        if(it->getDomain() == name){
            servers.erase(it);
            return true;
        }
    }

    return false;

};

bool DnsSearchServerList::compareDnsSearchServer(const DnsSearchServer& s1, const DnsSearchServer& s2){
    return (s1 == s2);
}

}





// /**
//  * @brief Get the list of DNS search domains.
//  * @return List of DNS search domains.
//  */
// DnsSearchList getSearchList()
// {
//     DnsSearchList search_list;
//     return search_list;
// }

