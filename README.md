##Homework assignment 3##
About
_____________________________________________________________________________________________________________________________________
This is a server and client where the client connect via ip and port and the server is started with a addres of a csv file and port number. the client will send info to the server and the server will preform the KNN algorithem. this algorithem acceptes as initial input a line where you first type the vector to be classified then the calculation methoud and then the k for it to calculate the k nearest nighbours with, the calculation methoud is a three letter combanation in upper case representing your desierd calculation methoud. valid three letter combanations for calculation methouds are:

AUC - Euclidean distance
MAN - Manhattan distance
CHB - Chebyshev distance
CAN - Canberra distance
MIN - Minkowski distance (here we use p = 2)

Then our code will wait indefinitly for a input vector of matching length to the data and return its prediction for the vectors classification.

When invalid input is enterd you will recive a invaild input message in return and be expected to input a new inputline.
Any invalid input enterd when starting the server or client will make the code exit the program.

In oreder to exit the program you are requierd to enter -1.
_____________________________________________________________________________________________________________________________________
Running the code
_____________________________________________________________________________________________________________________________________
In order to run the our code make sure it exists in your current directory and path and use the command make in order to build it.

then use server.out "address" "port" for windows or ./server.out "address" "port" for linux in order to run the server,
and use client.out "ip" "port" for windows or ./client.out "ip" "port" for linux in order to run the client.

then you will be able to enter the inputs.
_____________________________________________________________________________________________________________________________________
Invalid inputs
_____________________________________________________________________________________________________________________________________
- Any k that is not a positive integer.
- Any incorrect address.
- Any non existing calculation methoud.
- Any vector not in the same length as data vector.
- Any data entered to the vector which is not a double.
- invalid ip.
- invalid port number.

Thank you for running our code :)
