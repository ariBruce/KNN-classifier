#include <iostream>
#include <regex>
#include "Client.hpp"

int main(int argc, char* argv[]){
    if (argc != 3)
    {
        throw invalid_argument( "invalid input in main client" );
    }
    
    std::string ip = argv[1];
    std::string port = argv[2];
    try {
        stoi(port);
    } catch (...) {
        throw invalid_argument( "port not an integer" );
    }
    if(stoi(port) > 65536 || stoi(port) < 1023){
        throw invalid_argument( "invalid port" );
    }
    std::regex ip_regex("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
    if (!std::regex_match(ip, ip_regex)) {
        throw invalid_argument( "invalid ip" );
    }
    Client myClient(ip, port);
    myClient.run();
    return 0;
}