#ifndef Command2_H_
#define Command2_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command.hpp"

class Command2 : public Command {
    public:
        Command2(DefaultIO*);
        ~Command2();
        void Validate_algorithem_settings(std::string input);
        void execute();



};

#endif