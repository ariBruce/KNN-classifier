#ifndef Command3_H_
#define Command3_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command.hpp"


class Command3 : public Command{
    public: 
    Command3(DefaultIO*);
    ~Command3();
    void execute();


};
#endif