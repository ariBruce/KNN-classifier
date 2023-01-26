##shira & aryeh
CC = g++
CFLAGS = -std=c++11

both: client.out server.out

client.out: MainClient.o Client.o SocketIO.o StandardIO.o
	$(CC) $(LDFLAGS) MainClient.o Client.o SocketIO.o StandardIO.o -o client.out

server.out: DistancesCalculate.o Knn.o SocketIO.o StandardIO.o Command.o Command1.o Command2.o Command3.o Command4.o CLI.o server.o MainServer.o 
	$(CC) $(CFLAGS) DistancesCalculate.o Knn.o SocketIO.o StandardIO.o Command.o Command1.o Command2.o Command3.o Command4.o CLI.o server.o MainServer.o -o server.out

Client.o: Client.cpp
	$(CC) $(CFLAGS) -c Client.cpp -o Client.o

MainClient.o: MainClient.cpp
	$(CC) $(CFLAGS) MainClient.cpp -c

MainServer.o: MainServer.cpp
	$(CC) $(CFLAGS) MainServer.cpp -c

DefaultIO.o: DefaultIO.hpp
	$(CC) $(CFLAGS) DefaultIO.hpp -c

DistancesCalculate.o: DistancesCalculate.cpp DistancesCalculate.hpp
	$(CC) $(CFLAGS) DistancesCalculate.cpp -c

Knn.o: Knn.cpp Knn.hpp
	$(CC) $(CFLAGS) Knn.cpp -c

server.o: server.cpp server.hpp
	$(CC) $(CFLAGS) server.cpp -c

Command.o: Command.cpp Command.hpp
	$(CC) $(CFLAGS) Command.cpp -c

Command3.o: Command3.cpp Command3.hpp
	$(CC) $(CFLAGS) Command3.cpp -c

Command1.o: Command1.cpp Command1.hpp
	$(CC) $(CFLAGS) Command1.cpp -c

Command2.o: Command2.cpp Command2.hpp
	$(CC) $(CFLAGS) Command2.cpp -c

Command4.o: Command4.cpp Command4.hpp
	$(CC) $(CFLAGS) Command4.cpp -c

CLI.o: CLI.cpp CLI.hpp
	$(CC) $(CFLAGS) CLI.cpp -c


StandardIO.o: StandardIO.cpp StandardIO.hpp
	$(CC) $(CFLAGS) StandardIO.cpp -c

SocketIO.o: SocketIO.cpp SocketIO.hpp
	$(CC) $(CFLAGS) SocketIO.cpp -c

clean:
	rm *.o server.out