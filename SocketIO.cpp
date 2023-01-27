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
    std::string temp_data = "";
    char buffer = 0;
    // clear the buffer
    // read data from the client
    while (buffer != '$') {
        int n = recv(userID, &buffer, sizeof(char), 0);
        if (n < 0) {
            std::cout<<"we are n<0 in socketIO";
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        } else if (n == 0){
            std::cerr << "Connection closed by the client" << std::endl;
            exit(1);
        } else {
            temp_data += buffer;
        }
    }
    //return everything but the $
    return temp_data.substr(0,temp_data.length()-1);
}

void SocketIO::write(string text) {
//send data to client
    text += "$";
    int n = send(userID, text.c_str(), text.size() + 1, 0);
    if (n < 0) {
        std::cerr << "ERROR: writing to socket" << std::endl;
        exit(1);
    }
}

SocketIO::~SocketIO() {}