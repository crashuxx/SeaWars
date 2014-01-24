/* 
 * File:   NetServer.h
 * Author: c
 *
 * Created on 24 styczeń 2014, 10:26
 */

#ifndef NETSERVER_H
#define	NETSERVER_H

#include <stdio.h>
#include <sys/types.h> 
#include <winsock2.h>

#include <vector>
#include <string>

#include "Net.h"

class NetServer : public Net {
public:
    NetServer();
    ~NetServer();
    
    bool start();
    
    void handle();
    void write(std::string& text);
    
    std::string* getCommand();
private:
    int receive(int fromSocket, char* buf, int size);
    
    int sockfd;
    int clientfd;
    
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    
    fd_set master;
    fd_set read_fds;
    
    int fdmax;
    
    int bufforPosition;
    char buffor[1024];
    std::vector<std::string*> commands;
};

#endif	/* NETSERVER_H */

