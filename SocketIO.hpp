#ifndef SocketIO_H_
#define SocketIO_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Knn.hpp"
#include "DefaultIO.hpp"

class SocketIO : public DefaultIO {
    int userID;
    public:
    SocketIO(int);
    ~SocketIO();
    std::string read();
    void write(std::string text);

};

#endif