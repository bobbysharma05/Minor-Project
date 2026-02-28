#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#define PORT "9034"

int get_listener_socket() {

    int yes = 1, listener;
    struct addrinfo hints, *res, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int rev = getaddrinfo(NULL, PORT, &hints, &res);
    if(rev != 0) {
        cout << gai_strerror(rev) << endl;  
        exit(1);
    }

    for(p=res; p != NULL; p = p -> ai_next) {
        listener = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol);
        
        if(listener < 0) {
            continue;
        }

        if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            continue;
        }

        if(bind(listener, p -> ai_addr, p -> ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    if(p == NULL) {
        return -1;
    }

    return listener;    
}

int main() {
    int listner;

    int fd_size = 5, fd_count = 0;
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    listner = get_listener_socket();

    if(listener  == -1) {
        cout << "Failed to get listener socket" << endl;
        exit(1);
    }

    pfds[0].fd = listener;
    pfds[0].events = POLLIN;

    fd_count = 1;

    while(1) {

        int poll_count = poll(pfds, fd_count, -1);

        if(poll_count == -1) {
            perror("poll");
            exit(1);
        }

        process_connections(listener, &fd_count, &fd_size, &pfds);

    }
    free(pfds);

}