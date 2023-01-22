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
    int rows;
    Receiver(int);
    ~Receiver();
    void Action1();
    void Action2();
    void Action3();
    void Action4();
    void Action5();
    void readCsv(string csv_location);
    bool is_int(const std::string& s);
    bool is_metType(const std::string& s);
    void get_train();
    void get_test();
    void serverData();
    void classifyCsv();
    void printClassify();
    void saveClassify();
};

#endif