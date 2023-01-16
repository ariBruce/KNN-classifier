#ifndef Server_H_
#define Server_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <vector>
#include "Knn.hpp"


class Server {
 private:
  std::string csv_location;
  vector<double> doubleValues;
  int k = 0;
  std::string calculation_method;
  int vector_size_total = 0;
  int sockfd;
  int port;
  struct sockaddr_in serv_addr;
  struct sockaddr_in cli_addr;
 public:
  bool disconnect = false;
  Server(std::string port, std::string csv_location);
  void Bind();
  void Listen();
  int Accept();
  void Read_and_validate_input(int sockfd);
  void Write_Knn_result(int sockfd);
  //take the data from the excel and put it into structs into a vector    
  vector<data_struct> read_data();
  //check if the argument is double
  bool is_double(const std::string& s);
  //check if the argument is int
  bool is_int(const std::string& s);
};

#endif