# KNN classifier
_____________________________________________________________________________________________________________________________________
This is a server and client where the client connect via ip and port and the server is started with a address of a csv file and port number. The client will send info to the server and the server will send it a menu containing five options to choose from. they are the following-

1. upload an unclassified csv data file 
2. algorithem settings
3. classify data
4. display resualts 
5. download results
8. exit

In order to choose a option the user will press the number associated to the command in the menu.

option 1 - upload an unclassified csv data file
_____________________________________________________________________________________________________________________________________
Here the user will be asked to submit a classified csv data file in order for the server to proccess it and afterward it will ask for the unclassified data file that needs to be classified by the knn algorithem according to the classified file.

when the upload is compleate "upload compleate" will be printed.

option 2 - algorithem settings
_____________________________________________________________________________________________________________________________________
Here the settings of the knn will be presented and the user will be asked to submit a new k and calculation method. The k needs to be positive and if enter is pressed the server will return to the menu.

The accepted algorithem settings are-

AUC - Euclidean distance
MAN - Manhattan distance
CHB - Chebyshev distance
CAN - Canberra distance
MIN - Minkowski distance (here we use p = 2)

option 3 - classify data
_____________________________________________________________________________________________________________________________________
this will make the server classify the test file.

option 4 - display resualts
_____________________________________________________________________________________________________________________________________
this will display the results for the test file in order and print done in the end.

option 5 - download results
_____________________________________________________________________________________________________________________________________
this will open a file in the requested server directory of the results displayed by the knn file.

option 8 - exit
_____________________________________________________________________________________________________________________________________
the client will exit the code
Running the code
_____________________________________________________________________________________________________________________________________

In order to run the our code make sure it exists in your current directory and path and use the command make in order to build it.

then use server.out "port" for windows or ./server.out "port" for linux in order to run the server,
and use client.out "ip" "port" for windows or ./client.out "ip" "port" for linux in order to run the client.

then you will be able to enter the inputs.
_____________________________________________________________________________________________________________________________________
Invalid inputs
_____________________________________________________________________________________________________________________________________
- Any k that is not a positive integer.
- Any incorrect address.
- Any non existing calculation methoud.
- Any incorrect file format or nonexisting file.
- invalid ip.
- invalid port number.

Thank you for running our code :)
