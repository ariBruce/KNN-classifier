#ifndef Command5_H_
#define Command5_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include <thread>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command.hpp"

class Command5 : public Command {
    public: 
    Command5(DefaultIO*);
    ~Command5();
    void execute();


};


#endif