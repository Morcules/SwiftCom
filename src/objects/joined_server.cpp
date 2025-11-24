#include "objects.hpp"

using JoinedServer = objects::JoinedServer;

objects::JoinedServer::JoinedServer(const uint16_t server_id, const in_addr server_ip_address, const ServerStatus status) : server_id(server_id), server_ip_address(server_ip_address), status(status) {};

uint16_t objects::JoinedServer::GetServerId() {
    return this->server_id;
}

in_addr objects::JoinedServer::GetServerIpAddress() {
    return this->server_ip_address;
}

JoinedServer::ServerStatus JoinedServer::GetServerStatus() {
    return this->status;
}
