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
        std::string classifications = "";
        for (int i = 1; i <= this->dio->recived_testing.size(); i++) {
            classifications.append(this->dio->recived_testing[i-1].label);
            classifications.append(",");
        }
            this->dio->write(classifications);
    }
}