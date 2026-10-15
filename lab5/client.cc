/*Using TCP/IP sockets, write a client – server program to make the client send the file name and 
to make the server send back the content of the requested file if present*/

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int s;
    char filename[100], buffer[1000];

    s = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (sockaddr*)&server, sizeof(server));

    cout << "Enter file name: ";
    cin >> filename;

    send(s, filename, strlen(filename) + 1, 0);

    cout << "\nFile contents:\n";

    while (true)
    {
        recv(s, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, "END") == 0)
            break;

        cout << buffer << endl;

        if (strcmp(buffer, "File not found") == 0)
            break;
    }

    close(s);

    return 0;
}