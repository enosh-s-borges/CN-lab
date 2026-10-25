
#include <iostream>
#include <fstream>
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
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (sockaddr*)&server, sizeof(server));
    listen(s, 5);

    cout << "Server ready for connection" << endl;
    int c = accept(s, NULL, NULL);

    char fname[100], buffer[1000];
    int n = recv(c, fname, sizeof(fname) - 1, 0);
    if (n <= 0) { close(c); close(s); return 0; }
    fname[n] = '\0';

    ifstream file(fname);
    if (!file)
        send(c, "404 File not found", 19, 0);
    else
    {
        while (file.getline(buffer, sizeof(buffer)))
            send(c, buffer, strlen(buffer) + 1, 0);
    }

    close(c);
    close(s);
    return 0;
}