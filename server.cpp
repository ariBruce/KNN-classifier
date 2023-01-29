#include "server.hpp"

Server::Server(std::string port) {
  if (!is_int(port)) {
  std::cerr << "ERROR: no port provided" << std::endl;
  }
  this -> port = stoi(port);
  this -> sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "ERROR opening socket" << std::endl;
    exit(1);
  }
  std::vector<std::thread> thread_vector;
};

void Server::Bind() {
  // clear address structure
  bzero((char *) &serv_addr, sizeof(serv_addr));

  // setup the host_addr structure for use in bind call
  this -> serv_addr.sin_family = AF_INET;

  // automatically be filled with current host's IP address
  inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr); //input binding information

  // convert the short integer value for port
  this -> serv_addr.sin_port = htons(this-> port);

  // bind the socket to the current IP address on port
  if (bind(this-> sockfd, (struct sockaddr *) &serv_addr, sizeof(this-> serv_addr)) < 0) {
    std::cerr << "ERROR on binding" << std::endl;
    exit(1);
  }
};

// listen for incoming connection requests
void Server::Listen() {
  listen(this-> sockfd, 5);
};

void Server::Start() {
  while (true) {
      //accept a new client connection
      int client_fd = accept(this->sockfd, nullptr, nullptr);
      if (client_fd < 0) {
          std::cerr << "Error accepting client connection" << std::endl;
          continue;
      }
      //create a new thread for the client
      std::thread threadObj(std::bind(&Server::handle, this, client_fd));
      //add the thread to the list of client threads
      this->thread_vector.push_back(std::move(threadObj));
      if (this->thread_vector.empty()) {
        break;
      }
  }
};

void Server::Stop() {
    stopRun = true;
    t->join(); // do not delete this!
};

Server::~Server() {
    delete this->t;
};

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

void Server::handle(int clientID){
  SocketIO sio(clientID);
  CLI cli(&sio);
  cli.start();
};