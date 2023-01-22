#include "Server.h"

Server::Server(std::string port) {
    stopRun = false;
    if (!is_int(port)) {
        std::cerr << "ERROR: no port provided" << std::endl;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
      std::cerr << "ERROR opening socket" << std::endl;
      exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(stoi(port));
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(this -> serv_addr)) < 0) {
      std::cerr << "ERROR on binding" << std::endl;
      exit(1);
    }
}

void Server::start(ClientHandler &ch) throw(const char *) {
    t = new thread([&ch, this]() {
        while (!stopRun) {
            cout << "Waiting for a client" << endl;
            socklen_t clientSize = sizeof(this->client);
            alarm(3);
            int aCLient = accept(fd, (struct sockaddr *) &client, &clientSize);
            if (aCLient < 0) {
                throw "Accept has failed";
            }
            cout << "Client connected" << endl;
            ch.handle(aCLient);
            close(aCLient);
            sleep(2);
        }
        close(fd);
    });
}

void Server::stop() {
    stopRun = true;
    t->join(); // do not delete this!
}

Server::~Server() {
    delete this->t;
}