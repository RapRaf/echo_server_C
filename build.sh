cd SERVER
gcc -o server main.c input.c application.c socket.c
cd ../CLIENT
gcc -o client main.c input.c application.c socket.c