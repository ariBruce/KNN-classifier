#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Knn.hpp"
#include "SocketIO.hpp"
using namespace std;


SocketIO::SocketIO(int userID) {
    this->userID = userID;
}

string SocketIO::read() {
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
            std::cout << buffer;
            bzero(buffer, 4096);
            temp_data.append(buffer, sizeof(buffer));
        }
    }
    return temp_data;
}

void SocketIO::write(string text) {
//send data to client
int n = send(userID, text.c_str(), text.size() + 1, 0);
    if (n < 0) {
        std::cerr << "ERROR: writing to socket" << std::endl;
        exit(1);
    }
}

void SocketIO::write(float f) {
    //send data to client
    int n = send(userID, to_string(f).c_str(), to_string(f).size() + 1, 0);
    if (n < 0) {
        std::cerr << "ERROR: writing to socket" << std::endl;
        exit(1);
    }
}

SocketIO::~SocketIO() {}