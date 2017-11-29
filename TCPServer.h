#ifndef UNTITLED_TCPSERVER_H
#define UNTITLED_TCPSERVER_H

#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

#define TRUE   1
#define FALSE  0
#define PORT 8888
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 30

class TCPServer{
public:
    void initialize(int* client_socket, int& master_socket, int& opt,sockaddr_in& address,int& addrlen);
    void checkForChilds(fd_set* readfds,int& max_sd,int& master_socket,int& sd,int* client_socket);
    void acceptConnection(int& new_socket,int& master_socket,sockaddr_in& address,int& addrlen,int* client_socket);
    void disconnectClient(int& sd,sockaddr_in& address, int& addrlen,int* client_socket, int i);
    std::string bufferToString(char* buffer);
    void start();
    //rmMap<int,std::string>* clients_maps[MAX_CLIENTS];
    int number_of_clients,total_var,memory_used;
    void ParseIncomingMessage(std::string message,int i,int sd);
};

#endif //UNTITLED_TCPSERVER_H
