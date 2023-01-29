#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Knn.hpp"
#include "StandardIO.hpp"


using namespace std;

StandardIO::StandardIO() {
}
StandardIO::~StandardIO(){
}

string StandardIO::read() {
    string str;
    getline(cin, str);
    return str;
}

void StandardIO::write(string text) {
    std::cout << text + "\n";
}


