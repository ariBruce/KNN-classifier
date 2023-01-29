#ifndef CLI_H_
#define CLI_H_

#include "stdlib.h"
#include <vector>
#include <string.h>
#include "Command.hpp"
#include "Knn.hpp"
#include "DefaultIO.hpp"
#include "Command1.hpp"
#include "Command2.hpp"
#include "Command3.hpp"
#include "Command4.hpp"

using namespace std;

class CLI {
    DefaultIO *dio;
    vector<data_struct> recived_learning;
    vector<data_struct> recived_testing;
    vector<Command*> allCommands;

    // you can add data members
    public:
    CLI(DefaultIO*);

    void start();

    void print_menu();

    ~CLI();
};

#endif /*CLI_H_*/
