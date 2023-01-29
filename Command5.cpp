#include "Command5.hpp"
using namespace std;


  Command5::Command5(DefaultIO* dio) : Command(dio){
      this ->dio = dio;
      this->Description = "download results";
  }

  Command5::~Command5()
  {
  }

  void Command5::execute(){
    if (this->dio->this->dio->recived_testing.empty()) {
        dio->write("please upload data");
        return;
    } else if (this->dio->recived_testing[0].label == "Needs testing") {
        this->dio->write("please classify the data");
        return;
    } else {
        dio->write("Please enter file path");
        if (dio->read() == "valid") {
            //TODO: create thread to handle the download
            send();
        }
    }
  }