/*Write  a  program  on  datagram  socket  for  client/server  to  display  the messages on client side, typed at the server side.*/

//server side

/*
1. Open Terminal 1, compile and run the server: g++ server.cpp-o server; ./server 
2. Open Terminal 2, compile and run the client: g++ client.cpp-o client ./client 
3. Go back to Terminal 1 (Server), type a message, and press Enter to see it on the client side.
*/

#include<iostream> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 

int main(){ 
    //1. Create UDP socket and bind to port 8080 
    int server= socket(AF_INET, SOCK_DGRAM, 0); 
    struct sockaddr_in saddr= {AF_INET,htons(8080), INADDR_ANY}; 
    bind(server, (struct sockaddr*)&saddr, sizeof(saddr)); 
    std::cout<< "Waiting for client..."<< std::endl; 
    //2. Wait for client to ping so we get their address 
    struct sockaddr_in caddr; 
    socklen_t len = sizeof(caddr); 
    char buf[1024]; 
    recvfrom(server, buf, 1024, 0, (struct sockaddr*)&caddr, &len); 
    std::cout<< "Client connected! Type messages below:\n"; 
    //3. Read typing from console and send to client 
    while(true){ 
        std::string msg; 
        std::getline(std::cin, msg); 
        sendto(server, msg.c_str(), msg.length(), 0, (struct sockaddr*)&caddr, len); 
    } 
    close(server); 
    return 0; 
}