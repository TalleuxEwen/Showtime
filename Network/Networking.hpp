//
// Created by talleux on 2/23/24.
//

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <vector>

class ServerSocket
{
    public:
        ServerSocket();
        ~ServerSocket() = default;
        int acceptClient();
        void setFDset();
        int selectFd();

        std::vector<int> getClients();

        int _socket;
        int _client{};
        struct sockaddr_in _server{};
        struct sockaddr_in _clientAddress{};
        int _clientAddressLength;
        int _port;
        bool _connected;
        fd_set _readfds{};
        timeval _timeout = {0, 1};
        std::vector<int> _clients;
};
