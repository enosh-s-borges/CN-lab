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
    char filename[100];
    char buffer[1000];

    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("Bind failed");
        close(s);
        return 1;
    }

    listen(s, 5);

    cout << "Waiting for client..." << endl;

    c = accept(s, NULL, NULL);

    if (c < 0)
    {
        perror("Accept failed");
        close(s);
        return 1;
    }

    int n = recv(c, filename, sizeof(filename) - 1, 0);

    if (n <= 0)
    {
        close(c);
        close(s);
        return 1;
    }

    filename[n] = '\0';

    ifstream file(filename);

    if (!file)
    {
        const char* msg = "File not found\n";
        send(c, msg, strlen(msg), 0);
    }
    else
    {
        while (file.getline(buffer, sizeof(buffer)))
        {
            strcat(buffer, "\n");

            send(c, buffer, strlen(buffer), 0);
        }

        file.close();
    }

    shutdown(c, SHUT_WR);
    close(c);
    close(s);

    return 0;
}