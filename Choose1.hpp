#ifndef Choose1_H_
#define Choose1_H_

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
#include "Receiver.hpp"
#include "client.hpp"
using namespace std;



class Choose1 : Command
{
    public:
    Receiver* receiver1;
    string path;
    Choose1(Receiver*, int);
    ~Choose1();
    void execute() override;
    void readCsv(string csv_location);
    bool is_double(const std::string& s);
    void get_train_path();
    void get_test_path();
};

#endif