#ifndef Receiver_H_
#define Receiver_H_

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Command.hpp"
#include "client.hpp"
using namespace std;

class Receiver{
    public:
    int sock;
    Receiver(int);
    ~Receiver();
    void Action1();
    void Action2();
    void readCsv(string csv_location);
    bool is_double(const std::string& s);
    void get_train();
    void get_test();
    void serverData();
};

#endif