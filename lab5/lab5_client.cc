/*Using TCP/IP sockets, write a client – server program to make the client send the file name and 
to make the server send back the content of the requested file if present*/

//client

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int s;
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
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(s, (sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("Connection failed");
        close(s);
        return 1;
    }

    cout << "Enter file name: ";
    cin >> filename;

    send(s, filename, strlen(filename) + 1, 0);

    cout << "\nFile contents:\n";

    int n;

    while ((n = recv(s, buffer, sizeof(buffer), 0)) > 0)
    {
        cout.write(buffer, n);
    }

    if (n < 0)
        perror("Receive failed");

    close(s);

    return 0;
}