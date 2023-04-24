#include "dns.hpp"
#include <sdbus-c++/sdbus-c++.h>
#include <sysrepo.h>

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

bool DnsServer::operator==(const DnsServer& other) const {
     return (this->Name == other.Name);
}

bool DnsServer::operator!=(const DnsServer& other) const { 
    return (this->Name == other.Name); 
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

//implementation of DnsSearchServer

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

DnsSearchServerList& DnsSearchServerList::getInstance(){
    static DnsSearchServerList list;
    return list;
}

DnsSearchServerList::DnsSearchServerList(){};

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

std::optional<DnsSearchServer> DnsSearchServerList::findDnsSearchServer(const std::string& domain){

    for(DnsSearchServer& server : servers){
        if(server.getDomain() == domain){
            return server;
        }
    }
    
    return std::nullopt;
}

bool DnsSearchServerList::removeDnsSearchServer(const std::string& domain){

    std::vector<DnsSearchServer>::iterator it = servers.begin();

    for(it; it != servers.end(); it++){
        if(it->getDomain() == domain){
            servers.erase(it);
            return true;
        }
    }

    return false;

};

bool DnsSearchServerList::compareDnsSearchServer(const DnsSearchServer& s1, const DnsSearchServer& s2){
    return (s1 == s2);
}

std::vector<DnsServer> DnsServerList::servers;

void DnsServerList::clearList(){
    servers.clear();
}

bool DnsServerList::addDnsServer(const DnsServer& srv){
    for (DnsServer& server : servers){
        if(server == srv){
            //already exists
            return false;
        }
    }

    servers.push_back(srv);
    return true;
}

std::optional<DnsServer> DnsServerList::findDnsServer(const std::string& name){

    for(DnsServer& server : servers){
        if(server.getName() == name){
            return server;
        }
    }
    
    return std::nullopt;
}

bool DnsServerList::removeDnsServer(const std::string& name){

    std::vector<DnsServer>::iterator it = servers.begin();

    for(it; it != servers.end(); it++){
        if(it->getName() == name){
            servers.erase(it);
            return true;
        }
    }

    return false;

}

bool DnsServerList::compareDnsServer(const DnsServer& s1, const DnsServer& s2){
    return (s1 == s2);
}

//standalone functions
// #define SYSTEMD 
// #define SYSTEMD_IFINDEX 1
int changeSearchServer(DnsSearchServer searchServer){

    auto bus = sdbus::createSystemBusConnection();
    

//     int error = 0;

//     const char* dns_domain = searchServer.getDomain().c_str();
//     const int search_type = searchServer.getSearch();

//     #ifdef SYSTEMD
//         int r = 0;
//         sd_bus_error sdb_err = SD_BUS_ERROR_NULL;
// 	    sd_bus_message *msg = nullptr;
// 	    sd_bus_message *reply = nullptr;
// 	    sd_bus *bus = nullptr;

//        r = sd_bus_open_system(&bus);
// 	if (r < 0) {
// 		// SRPLG_LOG_ERR(PLUGIN_NAME, "Failed to open system bus: %s\n", strerror(-r));
// 		goto invalid;
// 	}

//     r = sd_bus_message_new_method_call(
// 		bus,
// 		&msg,
// 		"org.freedesktop.resolve1",
// 		"/org/freedesktop/resolve1",
// 		"org.freedesktop.resolve1.Manager",
// 		"SetLinkDomains");
// 	if (r < 0) {
// 		goto invalid;
// 	}

//     // set ifindex to the first value in the list
// 	r = sd_bus_message_append(msg, "i", SYSTEMD_IFINDEX);
// 	if (r < 0) {
// 		// SRPLG_LOG_ERR(PLUGIN_NAME, "sd_bus_message_append() error");
// 		goto invalid;
// 	}

//     r = sd_bus_message_open_container(msg, 'a', "(sb)");
// 	if (r < 0) {
// 		// SRPLG_LOG_ERR(PLUGIN_NAME, "sd_bus_message_open_container() error");
// 		goto invalid;
// 	}

    

//     r = sd_bus_message_append(msg, "(sb)", dns_domain , search_type);
// 		if (r < 0) {
// 			//SRPLG_LOG_ERR(PLUGIN_NAME, "sd_bus_message_append() error");
// 			goto invalid;
// 		}
//     r = sd_bus_message_close_container(msg);
// 	if (r < 0) {
// 		//SRPLG_LOG_ERR(PLUGIN_NAME, "sd_bus_message_close_container() error");
// 		goto invalid;
// 	}

// 	r = sd_bus_call(bus, msg, 0, &sdb_err, &reply);
// 	if (r < 0) {
// 		//SRPLG_LOG_ERR(PLUGIN_NAME, "sd_bus_call() error");
// 		goto invalid;
// 	}

// 	// SRP_LOG_INF("Set domains successfully!");
// 	goto finish;

// invalid:
// 	//SRPLG_LOG_ERR(ietf::sys::PLUGIN_NAME, "sd-bus failure (%d): %s", r, sdb_err.message);
// 	error = -1;

// finish:
// 	sd_bus_message_unref(msg);
// 	sd_bus_flush_close_unref(bus);
	
//     #endif //SYSTEMD


//     return error;
return 0;
}

}// end of namespace


