#ifndef StandardIO_H_
#define StandardIO_H_

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


class StandardIO : public DefaultIO {
    public:
    StandardIO();
    ~StandardIO();
    string read();
    void write(string text);


};

#endif