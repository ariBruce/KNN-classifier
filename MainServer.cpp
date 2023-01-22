#include <iostream>
#include <thread>
#include "server.hpp"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "not enough arguments";
  }
  std::string port = argv[2];
  try {
        stoi(port);
    } catch (...) {
        throw invalid_argument( "port not an integer" );
    }
    if(stoi(port) > 65536 || stoi(port) < 1023){
        throw invalid_argument( "invalid port" );
    }
  Server server(port, argv[1]);
  server.Bind();
  server.Listen();
  std::vector<std::thread> clientThreads;
  while (true) {
      int clientSocket = server.Accept();
      server.Send_menu(client_sockfd);
      server.Read_menu_choice(client_sockfd);
      clientThreads.emplace_back(handleClient, clientSocket);
  }
  int client_sockfd = server.Accept();
  /*//if you wanted the server to disconnect 
  //after it handled all its connections enter this if statment
  if (server.disconnect == true) {
    break;
  }*/
  while (true) {
    
    if (server.disconnect == true) {
      break;
    }
    server.Write_Knn_result(client_sockfd);
  }
  return 0;
}