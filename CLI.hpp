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
    // you can add data members
public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();
};

#endif /*CLI_H_*/
