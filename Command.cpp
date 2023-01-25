#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include "Knn.hpp"
#include "Command.hpp"


Command::Command(DefaultIO* dio){
    this ->dio = dio;
};

//void Command::execute();

string Command::getDescription() {
    return this->Description;
};

//check if the string can be double
bool Command::is_double(const std::string& s) {
    std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
    return std::regex_match(s, double_regex);
};

//check if the string can be int
bool Command::is_int(const std::string& s)
    {
    try
    {
        std::stoi(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
};

Command::~Command() {};
