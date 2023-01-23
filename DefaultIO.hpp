#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Knn.hpp"
using namespace std;

class DefaultIO {
public:
    std::string distance_metric = "null";
    vector<data_struct> recived_learning;
    vector<data_struct> recived_testing;
    int k = 5;
    ofstream out;
    ifstream in;
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual ~DefaultIO() {}

};