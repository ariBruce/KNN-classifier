##shira & aryeh
CC = g++
CFLAGS = -std=c++11

both: server.out client.out

client.out: MainClient.o client.o 
	$(CC) $(CFLAGS) MainClient.o client.o -o client.out

server.out: MainServer.o DistancesCalculate.o Knn.o server.o 
	$(CC) $(CFLAGS) MainServer.o DistancesCalculate.o Knn.o server.o -o server.out

MainServer.o: MainServer.cpp
	$(CC) $(CFLAGS) MainServer.cpp -c

MainClient.o: MainClient.cpp
	$(CC) $(CFLAGS) MainClient.cpp -c

DistancesCalculate.o: DistancesCalculate.cpp DistancesCalculate.hpp
	$(CC) $(CFLAGS) DistancesCalculate.cpp -c

Knn.o: Knn.cpp Knn.hpp
	$(CC) $(CFLAGS) Knn.cpp -c

server.o: server.cpp server.hpp
	$(CC) $(CFLAGS) server.cpp -c

client.o: client.cpp client.hpp
	$(CC) $(CFLAGS) client.cpp -c

clean:
	rm *.o server.out
