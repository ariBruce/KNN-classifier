#ifndef Command4_H_
#define Command4_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command.hpp"

class Command4 : public Command {
    public: 
    Command4(DefaultIO*);
    ~Command4();
    void execute();


};


#endif