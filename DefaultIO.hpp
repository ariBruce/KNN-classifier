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
    std::string distance_metric = "AUC";
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

class StandardIO : public DefaultIO {

public:
    StandardIO(string inputFile, string outputFile) {
        in.open(inputFile);
        out.open(outputFile);
    }

    string read() {
        string str;
        in >> str;
        return str;
    }

    void write(string text) {
        out << text;
    }

    void write(float f) {
        out << f;
    }

    void read(float *f) {
        in >> *f;
    }
};

class SocketIO : public DefaultIO {
    int userID;
public:
    SocketIO(int userID) {
        this->userID = userID;
    }

    string read() {
        std::string temp_data;
        char buffer[4096];
        // clear the buffer
        bzero(buffer, 4096);
        // read data from the client
        while (true) {
        int n = recv(userID, buffer, sizeof(buffer), 0);
        if (n < 0) {
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        } else if (n == 0) {
            break;
        } else {
            temp_data.append(buffer, sizeof(buffer));
        }
        }
        return temp_data;
    }

    void write(string text) {
    //send data to client
    int n = send(userID, text.c_str(), text.size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
    }

    void write(float f) {
    //send data to client
    int n = send(userID, to_string(f).c_str(), to_string(f).size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
    }

};