/* 
 * File:   Net.h
 * Author: c
 *
 * Created on 24 styczeń 2014, 10:23
 */

#ifndef NET_H
#define	NET_H

#include <string>

class Net {
public:
    virtual ~Net() {}
    
    virtual bool start() = 0;
    
    virtual void handle() = 0;
    virtual void write(std::string& text) = 0;
    virtual std::string* getCommand() = 0;
    
    static Net* factory();
private:

};

#endif	/* NET_H */

