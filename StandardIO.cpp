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
#include "StandardIO.hpp"


using namespace std;

StandardIO::StandardIO(string inputFile, string outputFile) {
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

void StandardIO::write(string text) {
out << text;
}

void StandardIO::write(float f) {
out << f;
}

void StandardIO::read(float *f) {
in >> *f;
}