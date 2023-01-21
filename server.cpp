#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "server.hpp"
#include "Knn.hpp"

  Server::Server(std::string port, std::string csv_location) {
    if (!is_int(port)) {
    std::cerr << "ERROR: no port provided" << std::endl;
    }
    this -> csv_location = csv_location;
    this -> port = stoi(port);
    this -> sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
      std::cerr << "ERROR opening socket" << std::endl;
      exit(1);
    }
  };

  void Server::Bind() {
    // clear address structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // setup the host_addr structure for use in bind call
    this -> serv_addr.sin_family = AF_INET;

    // automatically be filled with current host's IP address
    inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr); //input binding information

    // convert the short integer value for port
    this -> serv_addr.sin_port = htons(this -> port);

    // bind the socket to the current IP address on port
    if (bind(this -> sockfd, (struct sockaddr *) &serv_addr, sizeof(this -> serv_addr)) < 0) {
      std::cerr << "ERROR on binding" << std::endl;
      exit(1);
    }
  };

  // listen for incoming connection requests
  void Server::Listen() {
    listen(this -> sockfd, 5);
  };

  int Server::Accept() {
    // accept a new connection request
    socklen_t clilen = sizeof(this -> cli_addr);
    int newsockfd = accept(this -> sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
      std::cerr << "ERROR on accept" << std::endl;
      exit(1);
    }
    return newsockfd;
  };

  //read csv from client
  void Server::Read_csv_recived(int client_sockfd) {
    std::string temp_data;
    char buffer[4096];
    // clear the buffer
    bzero(buffer, 4096);
    // read data from the client
    while (true) {
      int n = recv(client_sockfd, buffer, sizeof(buffer), 0);
      if (n < 0) {
        std::cerr << "ERROR reading from socket" << std::endl;
        exit(1);
      } else if (n == 0) {
        this -> disconnect = true;
        break;
      } else {
        temp_data.append(buffer, sizeof(buffer));
      }
    }
    this -> csv_recived_temp = temp_data;
  }

  //recive algorithem settings from client
  void Server::recive_algorithem_settings(int client_sockfd) {
    char buffer[4096];
    // clear the buffer
    bzero(buffer, 4096);
    int n = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (n < 0) {
      std::cerr << "ERROR reading from socket" << std::endl;
      exit(1);
    } else if (n == 0) {
      this -> disconnect = true;
      break;
    } else {
      //put the data from the csv into vector
      stringstream s(csv_sent);
      //when there are still data in the row
      while (getline(s,word,' ')) {
        if (is_int(word)) {
          this -> k = stoi(word);
        } else if (word == "AUC" || word == "MAN" || word == "CHB" || word == "CAN" || word == "MIN") {
          this->calculation_method = word;
        } else if (!is_int(word) || stoi(word) < 0){
            std::string error_message = 'invalid value for K';
            int n = send(client_sockfd, error_message.c_str(), error_message.size() + 1, 0);
            if (n < 0) {
              std::cerr << "ERROR: writing to socket" << std::endl;
              exit(1);
            }
        } else {
            std::string error_message = 'invalid value for metric';
            int n = send(client_sockfd, error_message.c_str(), error_message.size() + 1, 0);
            if (n < 0) {
              std::cerr << "ERROR: writing to socket" << std::endl;
              exit(1);
            }
        }
      }
    }
  };

  //take every row from the csv into a vector and recive the data with commas in between
  vector<data_struct> Server::read_data(std::string csv_sent)
  {
    //the struct we will return with the data
    vector<data_struct> data;
    //the classify
    string labels = "";
    string line, word, s;
    vector<double> tmp;
    int vector_size = 0;
    //put the data from the csv into vector
    stringstream s(csv_sent);
    //when there are still data in the row
    while (getline(s,word,','))
    {
        if (is_double(word))
        {
            tmp.push_back(stod(word));
            vector_size++;
            if (this->vector_size_total != 0 && vector_size == this->vector_size_total)
            {
              lables = "Needs testing";
            }
        }
        else { //will only occur for the training and not the testing file
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
    if(data[0].label == "Needs testing")
    {
      this ->csv_recived_testing = this ->csv_recived_temp;
    } else {
      this ->csv_recived_learning = this ->csv_recived_temp;
    }
    return data;
  };

  //check if the string can be double
  bool Server::is_double(const std::string& s) {
    std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
    return std::regex_match(s, double_regex);
  }
  
  //classifys the testing data
  void Server::Predict_Knn_result(int client_sockfd) {
    //if there is no data to test ask for it
    if (this -> csv_recived_testing == " " || csv_recived_learning == " "){
      std::string message = 'please upload data';
    } else {
      //use learning data and test data
      this -> recived_learning = read_data(this -> csv_recived_learning);
      this -> recived_testing = read_data(this -> csv_recived_testing);
      //build the Knn within loop for every test data
      for (int i = 0; i < this -> recived_testing.size(); i++) {
        Knn Knn_calc = Knn(this -> k, this -> recived_testing.points , this -> calculation_method);
        //run the algorithm
        Knn_calc.findKnearest(&classified_data);
        this -> recived_testing[i].label = Knn_calc.predict();
      }
        std::string message = 'classifying data complete';
    }
    //send data to client
    int n = send(client_sockfd, message.c_str(), message.size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
  };

  //returns the string as it should be printed
  void Server::Return_prediction(int client_sockfd) {
    if(this -> recived_testing == NULL) {
      std::string message = 'please upload data';
    } else if (this -> recived_testing[i].label == "Needs testing") {
        std::string message = 'please classify the data';
    } else {
      for (int i = 0; i =< this -> recived_testing.size(); i++) {
        std::string to_print;
        if (i == this -> recived_testing.size()) {
          to_print.append("Done.", 7)
        } else {
          to_print.append(to_string(i), sizeof(to_string(i)));
          to_print.append(" ", sizeof(" "));
          to_print.append(recived_testing[i].label, sizeof(recived_testing[i].label));
          to_print.append("\n", sizeof("\n"));
        }
      }
    }
    int n = send(client_sockfd, to_print.c_str(), to_print.size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
  }


  //check if the string can be int
  bool Server::is_int(const std::string& s)
    {
    try
    {
        std::stoi(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
  };