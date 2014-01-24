/* 
 * File:   NetClient.h
 * Author: c
 *
 * Created on 24 styczeń 2014, 12:10
 */

#ifndef NETCLIENT_H
#define	NETCLIENT_H

#include <stdio.h>
#include <sys/types.h> 
#include <winsock2.h>

#include <vector>
#include <string>

#include "Net.h"

class NetClient : public Net {
public:
    NetClient();
    ~NetClient();
    
    bool start();
    
    void handle();
    void write(std::string& text);
    
    std::string* getCommand();
private:
    int receive(int fromSocket, char* buf, int size);
    
    int sockfd;
    struct sockaddr_in their_addr;
    struct hostent * he;
    
    int bufforPosition;
    char buffor[1024];
    std::vector<std::string*> commands;

};

#endif	/* NETCLIENT_H */

