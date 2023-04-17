#include "dns.hpp"
#include "sdbus-c++/Message.h"
#include <sdbus-c++/sdbus-c++.h>

namespace ietf::sys::dns {

/**
 * @brief Default constructor.
 */
DnsServer::DnsServer()
    : Port(53){}


DnsServer::DnsServer(std::string name, std::string address, std::uint16_t port = 53)
    : Name{name},
     Address{address},
     Port{port} {}

void DnsServer::clear(){
    this->Address=""; // maybe NULL?
    this->Port = 53;
    this->Name = "" ;//maybe also NULL?
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

/**
 * @brief Get the list of DNS search domains.
 * @return List of DNS search domains.
 */
DnsSearchList getSearchList()
{
    DnsSearchList search_list;
    return search_list;
}

}