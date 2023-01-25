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
    string inputFile, outputFile;
    in.open(inputFile);
    out.open(outputFile);
}
StandardIO::~StandardIO(){

}

string StandardIO::read() {
    string str;
    in >> str;
    return str;
}

void StandardIO::read(float *f) {
    in >> *f;
}

void StandardIO::write(string text) {
    out << text;
}

void StandardIO::write(float f) {
    out << f;
}

