/* 
 * File:   NetServer.cpp
 * Author: c
 * 
 * Created on 24 styczeń 2014, 10:26
 */

#include <iosfwd>

#include "NetServer.h"
#include "Entity.h"
#include <unistd.h>
#include <fcntl.h>

NetServer::NetServer() {
    bufforPosition = 0;
    memset(buffor, 0, 1024);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6688);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(serv_addr.sin_zero), '\0', 8);
}

NetServer::~NetServer() {
}

bool NetServer::start() {
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof (serv_addr)) < 0) {
        return false;
    }

    listen(sockfd, 5);

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    FD_SET(sockfd, &master);
    fdmax = sockfd;

    return true;
}

int NetServer::receive(int fromSocket, char* buf, int size) {

    if (size <= 0) {
        return 0;
    }

    memcpy(((char*) &buffor) + bufforPosition, buf, size);
    bufforPosition += size;

    char* pos;
    
    do {
        pos = strchr(buffor, '\r');
        if (pos == NULL) {
            pos = strchr(buffor, '\n');
        }

        if (pos != NULL) {
            int length = ((int)pos)-((int)&buffor);

            if (length > 0) {
                std::string* cmd = new std::string(buffor, 0, length);
                commands.push_back(cmd);
            }

            char tmp[1024];
            memset(&tmp, 0, 1024);
            if( bufforPosition > 0 ) {
                memcpy(&tmp, ((char*) &buffor) + length + 1, bufforPosition - length - 1 );
            }
            memcpy(&buffor, &tmp, 1024);
            bufforPosition = 0;
        }
    } while(pos != NULL);
}

std::string* NetServer::getCommand() {

    std::string* cmd = NULL;

    if (commands.size() == 0) {
        return cmd;
    }

    cmd = (*(commands.begin()));
    commands.erase(commands.begin());

    return cmd;
}

void NetServer::write(std::string& text) {
    ::send(clientfd, text.c_str(), text.length(), 0);
}

void NetServer::handle() {

    char buf[ 256 ];
    int nbytes;

    timeval tv = {0, 50};

    memcpy(&read_fds, &master, sizeof (master));
    if (select(fdmax + 1, &read_fds, NULL, NULL, &tv) == -1) {
        perror("select");
        exit(1);
    }

    int addrlen;

    for (int i = 0; i <= fdmax; i++) {
        if (FD_ISSET(i, & read_fds)) {
            if (i == sockfd) {
                // new connection
                addrlen = sizeof ( cli_addr);
                if ((clientfd = accept(sockfd, (struct sockaddr *) & cli_addr,
                        & addrlen)) == -1) {
                    //                    perror("accept");
                } else {
                    FD_SET(clientfd, &master);
                    if (clientfd > fdmax) {
                        fdmax = clientfd;
                    }
                    /*                    printf("selectserver: new connection from %s on "
                                                "socket %d\n", inet_ntoa(cli_addr.sin_addr), clientfd);/**/
                }
            } else {
                // data
                if ((nbytes = recv(i, buf, sizeof (buf), 0)) <= 0) {
                    // error
                    if (nbytes == 0) {
                        //                        printf("selectserver: socket %d hung up\n", i);
                    } else {
                        //                        perror("recv");
                    }
                    closesocket(i);
                    FD_CLR(i, &master);
                } else {
                    receive(i, buf, nbytes);
                }
            }
        }
    }
}
