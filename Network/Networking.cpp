//
// Created by talleux on 2/23/24.
//

#include "Networking.hpp"

ServerSocket::ServerSocket()
{
    _port = 6969;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &_socket, sizeof(_socket));
    setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &_socket, sizeof(_socket));
    if (_socket == 0)
    {
        std::cerr << "Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = INADDR_ANY;
    _server.sin_port = htons(_port);
    if (bind(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(_socket, 3) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    _clientAddressLength = sizeof(_clientAddress);
    _connected = false;
}

int ServerSocket::acceptClient()
{
    _client = accept(_socket, (struct sockaddr *)&_clientAddress, (socklen_t *)&_clientAddressLength);
    if (_client < 0)
    {
        std::cerr << "Accept failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    _connected = true;
    return _client;
}

void ServerSocket::setFDset()
{
    FD_ZERO(&_readfds);
    FD_SET(_socket, &_readfds);
    for (int client : _clients)
    {
        FD_SET(client, &_readfds);
    }
}

int ServerSocket::selectFd()
{
    int selectValue = select(FD_SETSIZE, &_readfds, nullptr, nullptr, &_timeout);

    if (selectValue < 0)
    {
        std::cerr << "Select failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    return selectValue;
}

std::vector<int> ServerSocket::getClients()
{
    return _clients;
}
