#ifndef CLI_H_
#define CLI_H_

#include "stdlib.h"
#include <vector>
#include <string.h>
#include "Command.hpp"
#include "Knn.hpp"
#include "DefaultIO.hpp"

using namespace std;

class CLI {
    DefaultIO *dio;
    vector<data_struct> recived_learning;
    vector<data_struct> recived_testing;
    vector<Command *> allCommands;
    Command1 Com1;
    Command2 Com2;
    Command3 Com3;
    Command4 Com4;

    // you can add data members
public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();
};

#endif /*CLI_H_*/
