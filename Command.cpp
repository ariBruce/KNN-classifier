#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <regex>
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
    std::string trimmed_string = s;
    trimmed_string.erase(std::remove(trimmed_string.begin(), trimmed_string.end(), '\t'), trimmed_string.end());
    std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
    return std::regex_match(trimmed_string, double_regex);
};

//check if the string can be int
bool Command::is_int(const std::string& s) {
    std::regex int_regex("^[0-9]?$");
    return std::regex_match(s, int_regex);
};

Command::~Command() {};
