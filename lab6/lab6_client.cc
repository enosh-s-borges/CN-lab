/*Write  a  program  on  datagram  socket  for  client/server  to  display  the messages on client side, typed at the server side.*/

//client side

/*
1. Open Terminal 1, compile and run the server: g++ server.cpp-o server; ./server 
2. Open Terminal 2, compile and run the client: g++ client.cpp-o client ./client 
3. Go back to Terminal 1 (Server), type a message, and press Enter to see it on the client side.
*/

#include<iostream> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<unistd.h> 

int main(){ 
    //1. Create UDP socket 
    int client = socket(AF_INET, SOCK_DGRAM, 0); 
    struct sockaddr_in saddr = {AF_INET, htons(8080), inet_addr("127.0.0.1")}; 
    //2. Send a quick packet to let the server know we exist 
    sendto(client, "HI", 2, 0, (struct sockaddr*)&saddr, sizeof(saddr)); 
    std::cout << "Waiting for server messages...\n"; 
    //3. Receive and print messages from the server 
    char buf[1024]; 
    while (true) { 
        int bytes = recvfrom(client, buf, 1024, 0, NULL, NULL); 
        buf[bytes] = '\0'; // End the string 
        std::cout << "Server says: " << buf << std::endl; 
    } 
    close(client); 
    return 0; 
}