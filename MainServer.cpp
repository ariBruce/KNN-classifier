#include <iostream>
#include <thread>
#include "server.hpp"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "not enough arguments";
  }
  std::string port = argv[1];
  try {
        stoi(port);
    } catch (...) {
        throw invalid_argument( "port not an integer" );
    }
    if(stoi(port) > 65536 || stoi(port) < 1023){
        throw invalid_argument( "invalid port" );
    }
  Server server(port);
  server.Bind();
  server.Listen();
  server.Start(); // will run until threads are all shut
  server.Stop();
}