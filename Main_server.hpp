#ifndef MAIN_SERVER_H_
#define MAIN_SERVER_H_

#include <pthread.h>
#include <thread>
#include "CLI.h"

class Server {
    thread *t; // the thread to run the start() method in
    bool stopRun;
    int fd;
    sockaddr_in server;
    sockaddr_in client;

public:
    Server(int port);

    virtual ~Server();

    void start();

    void stop();
};

#endif /* MAIN_SERVER_H_ */