/*Using TCP/IP sockets, write a client – server program to make the client send the file name and 
to make the server send back the content of the requested file if present*/

/*1. Compile and run the server first:
g++ server.cpp -o server
./server
2. Open another terminal and run the client:
g++ client.cpp -o client
./client
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int s, c;
    char filename[100], buffer[1000];

    s = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (sockaddr*)&server, sizeof(server));
    listen(s, 5);

    cout << "Waiting for client..." << endl;

    c = accept(s, NULL, NULL);

    recv(c, filename, sizeof(filename), 0);

    ifstream file(filename);

    if (!file)
    {
        strcpy(buffer, "File not found");
        send(c, buffer, strlen(buffer) + 1, 0);
    }
    else
    {
        while (file.getline(buffer, 1000))
        {
            send(c, buffer, strlen(buffer) + 1, 0);
        }

        strcpy(buffer, "END");
        send(c, buffer, strlen(buffer) + 1, 0);

        file.close();
    }

    close(c);
    close(s);

    return 0;
}