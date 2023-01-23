
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command1.hpp"
#include "Command.hpp"
using namespace std;


Command1::Command1(DefaultIO* dio) : Command(dio){
    this->dio = dio;
    this->Description = "upload an unclassified csv data file";
}

Command1::~Command1()
{
}
  
  /*it should be read libe by line and the client should follow the following format
  std::ifstream file(csv_file_path);
  std::string line;
  while (std::getline(file, line)) {
    send(sockfd, line.c_str(), line.length(), 0);
  }
  */

vector<data_struct> Command1::transfer_data(std::string csv_sent) {
  //the struct we will return with the data
  vector<data_struct> data;
  //the classify
  string labels = "";
  string line, word, s;
  vector<double> tmp;
  int vector_size = 0;
  //put the data from the csv into vector
  stringstream ss(csv_sent);
  //when there are still data in the row
  while(getline(ss,word,','))
  {
      if (this->is_double(word))
      {
          tmp.push_back(stod(word));
          vector_size++;
          if (this->vector_size_total != 0 && vector_size == this->vector_size_total)
          {
              labels = "Needs testing";
          }
      } else { //will only occur for the training and not the testing file
          labels = word;
          if (this->vector_size_total == 0)
          {
              this->vector_size_total = vector_size;
          }
          //put the label and the pasrameters in the vector
          if ((labels == "") || (vector_size != this->vector_size_total))
          {
              throw invalid_argument( "Invalid CSV data!" );
          }
      }
      data_struct temp_struct;
      temp_struct.label = labels;
      temp_struct.points = tmp;
      data.push_back(temp_struct);
      tmp.clear();
      labels = "";
      vector_size = 0;
  }
  return data;
};

void Command1::execute(){
  this->dio->write("Please upload your local train CSV file.");
  this->dio->recived_learning = transfer_data(this->dio->read());
  this->dio->write("Upload complete.");
  this->dio->write("Please upload your local test CSV file.");
  this->dio->recived_testing = transfer_data(this->dio->read());
  this->dio->write("Upload complete.");
};