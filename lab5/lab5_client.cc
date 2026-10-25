
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(3300);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (sockaddr*)&server, sizeof(server));

    char fname[100], buffer[1000];
    cout << "Enter the filename: ";
    cin.getline(fname, 100);
    if (send(s, fname, strlen(fname) + 1, 0) == -1){
        perror("send");
        close(s);
        return 1;
    }

    cout << "File contents: \n";

    int n;
    while ((n = recv(s, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[n] = '\0';
        cout << buffer << endl;
        if (strcmp(buffer, "404 File not found") == 0)
            break;
    }

    close(s);
    return 0;
}