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
    //add all kinds of commands.
    //AlgoSettingCommand *settingCom;
    //AnomalyDetectCommand *detectionCom;
    //AnalyzeCommand *analyzeCom;
    //ExitCommand *exitCommand;
    //ShowResultsCommand *resultsCom;
    //UploadCommand *uploadCom;
    vector<Command *> allCommands;
    // you can add data members
public:
    CLI(DefaultIO *dio);

    void start();

    vector<data_struct> read_data(std::string csv_sent);

    virtual ~CLI();
};

#endif /* CLI_H_ */
