/* 
 * File:   NetClient.cpp
 * Author: c
 * 
 * Created on 24 styczeń 2014, 12:10
 */

#include "NetClient.h"

NetClient::NetClient() {

    if ((he = gethostbyname("localhost")) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(6688);
    their_addr.sin_addr = *((struct in_addr *) he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8);
    bufforPosition = 0;
}

bool NetClient::start() {
    if (connect(sockfd, (struct sockaddr *) & their_addr, sizeof (struct sockaddr)) == -1) {
        return false;
    }

    return true;
}

std::string* NetClient::getCommand() {
    
    std::string* cmd = NULL;
    
    if(commands.size() == 0 ) {
        return cmd;
    }
    
    cmd = (*(commands.begin()));
    commands.erase(commands.begin());
    
    return cmd;
}

int NetClient::receive(int fromSocket, char* buf, int size) {

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

void NetClient::handle() {
    
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);
    
    timeval tv = {0, 50};
    if (select(sockfd + 1, &read_fds, NULL, NULL, &tv) == -1) {
        perror("select");
        exit(1);
    }
    
    int nbytes;
    char buf[256];

    for (int i = 0; i <= sockfd; i++) {
        if (FD_ISSET(i, & read_fds)) {
            if (i == sockfd) {
                // data
                if ((nbytes = recv(i, buf, sizeof (buf), 0)) <= 0) {
                    // error
                    if (nbytes == 0) {
                        //printf("selectserver: socket %d hung up\n", i);
                    } else {
                        //perror("recv");
                    }
                    closesocket(i);
                    FD_CLR(i, &read_fds);
                } else {
                    receive(i, buf, nbytes);
                }
            }
        }
    }
}

void NetClient::write(std::string& text) {
    ::send(sockfd, text.c_str(), text.length(), 0);
}

NetClient::~NetClient() {
}

