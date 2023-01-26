#ifndef Command_H_
#define Command_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include "StandardIO.hpp"
#include "DefaultIO.hpp"
#include "Knn.hpp"

class Command {
  public:
    std::string Description = "empty";  //description of the command in the menu.
    std::string down = "\n";
    int vector_size_total;
    DefaultIO *dio;
    Command(DefaultIO*);
    virtual ~Command();
    virtual void execute() = 0;
    string getDescription();
    bool is_double(const std::string& s);
    bool is_int(const std::string& s);
};

#endif