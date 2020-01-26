Problem 2 readme
Compile both rpcclient.c and rpcserver.c using the following commands
rpcserver.c:
gcc -o server.out rpcserver.c

rpcclient.c:
gcc -o client.out rpcclient.c

Execute the server first with
./server

Next find the machine running the server with command hostname
Then execute the client with the command
./client hostname command