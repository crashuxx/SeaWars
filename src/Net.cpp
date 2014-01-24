/* 
 * File:   Net.cpp
 * Author: c
 * 
 * Created on 24 styczeń 2014, 10:23
 */

#include "Net.h"

#include "NetServer.h"
#include "NetClient.h"

Net* Net::factory() {
    
    Net* net = new NetServer();

    if(net->start()) {
        return net;
    } else {
        net = new NetClient();
        if(net->start()) {
            return net;
        }
    }
    
    return NULL;
}