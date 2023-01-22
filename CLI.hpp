#ifndef CLI_H_
#define CLI_H_

#include "stdlib.h"
#include <vector>
#include <string.h>
#include "Commands.hpp"
#include "Knn.hpp"

using namespace std;

class CLI {
    DefaultIO *dio;
    vector<data_struct> recived_learning;
    vector<data_struct> recived_testing;
    //all of commands
    Command1 *Com1(dio);
    Command2 *Com2(dio);
    Command3 *Com3(dio);
    Command4 *Com4(dio);
    //Command5 *Com5(dio);
    vector<Command *> allCommands;
    // you can add data members
public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();
};

#endif /* CLI_H_ */
