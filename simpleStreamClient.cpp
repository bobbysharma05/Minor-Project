#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT "3490"
#define MAXDATASIZE 100

void* get_in_addr(struct sockaddr *sa) {
    if(sa -> sa_family == AF_INET) return &(((struct sockaddr_in*)sa) -> sin_addr);
    return &(((struct sockaddr_in6*)sa) -> sin6_addr);   
}

int main(int argc, char *argv[]) {

    int rev, sockfd;
    struct addrinfo hints, *serverinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((rev = getaddrinfo(argv[1], PORT, &hints, &serverinfo)) != 0) {
        cout << gai_strerror(rev) << endl;
        return 1;
    }

    char s[INET6_ADDRSTRLEN];

    for(p=serverinfo; p != NULL; p = p -> ai_next) {
        if((sockfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        inet_ntop(p -> ai_family, get_in_addr((struct sockaddr *)p -> ai_addr), s, sizeof s);

        if(connect(sockfd, p -> ai_addr, p -> ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if(p == NULL) {
        cout << "client: failed to connect" << endl;
        return 2;
    } 

    inet_ntop(p -> ai_family, get_in_addr((struct sockaddr*)p -> ai_addr), s, sizeof s);
    cout << "Connection done with: " << s << endl;

    freeaddrinfo(serverinfo);

    char buf[MAXDATASIZE];
    int numberOfBytes;

    if((numberOfBytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numberOfBytes] = '\0';

    cout << "Received: " << buf << endl;

    close(sockfd);

    return 0;
}