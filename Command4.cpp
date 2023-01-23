
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command4.hpp"
#include "Command.hpp"
using namespace std;


  Command4::Command4(DefaultIO* dio) : Command(dio){
      this ->dio = dio;
      this->Description = "classify data";
  }

  Command4::~Command4()
  {
  }

  void Command4::execute(){
    if(this->dio->recived_testing.empty()) {
      this->dio->write("please upload data");
    } else if (this->dio->recived_testing[0].label == "Needs testing") {
      this->dio->write("please classify the data");
    } else {
      for (int i = 0; i <= this -> dio->recived_testing.size(); i++) {
        if (i == this-> dio->recived_testing.size()) {
          this->dio->write("Done.");
        } else {
          this->dio->write(to_string(i) + " " + this->dio->recived_testing[i].label);
        }
      }
    }
  }
  