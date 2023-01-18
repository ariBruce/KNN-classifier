#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <restbed>
#include "server.hpp"
#include "Knn.hpp"

using namespace restbed;


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

void Server::Read_and_validate_input(int client_sockfd) {
  char buffer[4096];
    // clear the buffer
  bzero(buffer, 4096);
    // read data from the client
  int n = recv(client_sockfd, buffer, sizeof(buffer), 0);
  if (n < 0) {
    std::cerr << "ERROR reading from socket" << std::endl;
    exit(1);
  } else if (n == 0) {
      this -> disconnect = true;
  } else {
    this -> disconnect = false;
      std::stringstream ss1;
      ss1 << buffer;
      std::string temp;
      while (!ss1.eof())
      {
          // for getting each word in the string and converting it into a double
        ss1 >> temp;

          // make sure we recived a double that dosn't end/start with a dot and is not empty
        if (is_double(temp))
        {
          // push the good value into the vector
          this -> doubleValues.push_back(stod(temp));
        } else {
          break;
        }
      }
      if (temp == "AUC" || temp == "MAN" || temp == "CHB" || temp == "CAN" || temp == "MIN") {
          this->calculation_method = temp;
      } else {
          this->calculation_method = "invalid";
      }
      ss1 >> temp;
      //make sure its a number with input checks
      if(is_int(temp)) this -> k = stoi(temp);
      if(!ss1.eof()) {
        this -> k = 0;
      }
  }
};

void Server::Write_Knn_result(int client_sockfd) {
  //preform knn
  vector<data_struct> data = read_data();
  if (this -> calculation_method == "invalid"  || this -> doubleValues.size() != this -> vector_size_total || this -> k < 1) {
      std::string bad_input = "invalid input";
      this ->doubleValues.clear();
      this ->k = 0;
      this ->calculation_method = "invalid";
      int n = send(client_sockfd, bad_input.c_str(), bad_input.size() + 1, 0);
      if (n < 0) {
        std::cerr << "ERROR: writing to socket" << std::endl;
        exit(1);
      }
  } else {
    //build the Knn
    Knn Knn_calc = Knn(this -> k, this -> doubleValues , this -> calculation_method);
    //run the algorithm
    Knn_calc.findKnearest(&data);
    std::string prediction = Knn_calc.predict();
    //send data to client
    int n = send(client_sockfd, prediction.c_str(), prediction.size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
    this ->doubleValues.clear();
    this ->k = 0;
    this ->calculation_method = "invalid";
    }
  };

  //take every row from the csv into a vector
    vector<data_struct> Server::read_data()
    {
        //open the file of csv type and throw exception if not
        ifstream file(this->csv_location);
        if(!file) 
        {
          throw invalid_argument( "Invalid file location" );
        } 
        //the struct we will return with the data
        vector<data_struct> data;
        //the classify
        string labels = "";
        string line, word, s;
        vector<double> tmp;
        int vector_size = 0;
        //put the data from the csv into vector
        //when there are still rows in the csv
        while (file >> line)
        {
            labels = "";
            vector_size = 0;
            stringstream s(line);
            //when there are still data in the row
            while (getline(s,word,','))
            {
                if (is_double(word))
                {
                    tmp.push_back(stod(word));
                    vector_size++;
                }
                else labels = word;
            }
            if (this->vector_size_total == 0)
            {
                this->vector_size_total = vector_size;
            }
            
            //put the label and the pasrameters in the vector
            if ((labels == "") || (vector_size != this->vector_size_total))
            {
                throw invalid_argument( "Invalid training data!" );
            }
            data_struct temp_struct;
            temp_struct.label = labels;
            temp_struct.points = tmp;
            data.push_back(temp_struct);
            tmp.clear();
        }
        file.close();
        return data;
    };

/*
    check if the string can be double
*/
bool Server::is_double(const std::string& s) {
  std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
  return std::regex_match(s, double_regex);
}
/*
    check if the string can be int
*/
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
