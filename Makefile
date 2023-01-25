#Aryeh and Shira

OBJS = DistancesCalculate.o Knn.o DefaultIO.o SocketIO.o StandardIO.o Command.o Command1.o Command2.o Command3.o Command4.o Command8.o CLI.o server.o MainServer.o Client.o MainClient.o
OUT	= server.out,client.out

OBJS0	= DistancesCalculate.o Knn.o DefaultIO.o SocketIO.o StandardIO.o Command.o Command1.o Command2.o Command3.o Command4.o Command8.o CLI.o server.o MainServer.o
SOURCE0	= DistancesCalculate.cpp Knn.cpp server.cpp MainServer.cpp CLI.cpp Command.cpp Command1.cpp Command2.cpp Command3.cpp Command4.cpp Command8.cpp DefaultIO.cpp SocketIO.cpp StandardIO.cpp
HEADER0	= DistancesCalculate.h Knn.h DefaultIO.h Command.h CLI.h server.h MainServer.h 
OUT0	= server.out

OBJS1	= DistancesCalculate.o Knn.o DefaultIO.o SocketIO.o StandardIO.o Command.o Command1.o Command2.o Command3.o Command4.o Command8.o CLI.o Client.o MainClient.o
SOURCE1	= DistancesCalculate.cpp Knn.cpp CLI.cpp Command.cpp Command1.cpp Command2.cpp Command3.cpp Command4.cpp Command8.cpp SocketIO.cpp StandardIO.cpp Client.cpp MainClient.cpp
HEADER1	= DistancesCalculate.h Knn.h DefaultIO.h Command.h CLI.h Client.h MainClient.h
OUT1	= client.out

CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: server.out client.out

server.out: $(OBJS0)
	$(CC) -g $(OBJS0) -o $(OUT0) $(LFLAGS)

client.out: $(OBJS1)
	$(CC) -g $(OBJS1) -o $(OUT1) $(LFLAGS)

DistancesCalculate.o: DistancesCalculate.cpp
	$(CC) $(FLAGS) DistancesCalculate.cpp -std=c11

Knn.o: Knn.cpp
	$(CC) $(FLAGS) Knn.cpp -std=c11

DefaultIO.o: DefaultIO.cpp
	$(CC) $(FLAGS) DefaultIO.cpp -std=c11

SocketIO.o: SocketIO.cpp
	$(CC) $(FLAGS) SocketIO.cpp -std=c11
	
StandardIO.o: StandardIO.cpp
	$(CC) $(FLAGS) StandardIO.cpp -std=c11

Command.o: Command.cpp
	$(CC) $(FLAGS) Command.cpp -std=c11

Command1.o: Command1.cpp
	$(CC) $(FLAGS) Command1.cpp -std=c11

Command2.o: Command2.cpp
	$(CC) $(FLAGS) Command2.cpp -std=c11
	
Command3.o: Command3.cpp
	$(CC) $(FLAGS) Command3.cpp -std=c11

Command4.o: Command4.cpp
	$(CC) $(FLAGS) Command4.cpp -std=c11

Command8.o: Command8.cpp
	$(CC) $(FLAGS) Command8.cpp -std=c11

CLI.o: CLI.cpp
	$(CC) $(FLAGS) CLI.cpp -std=c11

server.o: server.cpp
	$(CC) $(FLAGS) server.cpp -std=c11

MainServer.o: MainServer.cpp
	$(CC) $(FLAGS) MainServer.cpp -std=c11

Client.o: Client.cpp
	$(CC) $(FLAGS) Client.cpp -std=c11

MainClient.o: MainClient.cpp
	$(CC) $(FLAGS) MainClient.cpp -std=c11

clean:
	rm -f $(OBJS) $(OUT)