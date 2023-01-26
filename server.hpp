#ifndef SERVER_H_
#define SERVER_H_

#include <pthread.h>
#include <thread>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Knn.hpp"
#include "CLI.hpp"
#include "DefaultIO.hpp"
#include "SocketIO.hpp"


class Server {
    thread *t; // the thread to run the start() method in
    bool stopRun;
    int sockfd;
    int port;
    sockaddr_in serv_addr;
    sockaddr_in client;
    std::vector<std::thread> thread_vector;

public:
    Server(std::string port);

    ~Server();

    void Start();

    void Stop();

    bool is_int(const std::string& s);

    void Bind();

    void Listen();

    void handle(void *arg);
};

#endif /*SERVER_H_ */