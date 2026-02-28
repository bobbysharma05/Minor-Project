#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;

#define PORT "3490"
#define BACKLOG 10

int main(int argc, char *argv[]) {

    int sockfd, new_fd;
    sockaddr_storage their_addr;
    socklen_t addr_size;
    addrinfo hints, *res, *p;

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <hostname>" << endl;
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // Don't care for IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    getaddrinfo(NULL, PORT, &hints, &res);

    sockfd = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);

    bind(s, res -> ai_addr, res -> ai_addrlen);  

    listen(s, BACKLOG);

    addr_size = sizeof their_addr; 
    new_fd = accept(s, (sockaddr *)&their_addr, &addr_size);

 

    

    freeaddrinfo(res);

    return 0;
        
}
