#include <bits/stdc++.h>
#include <poll.h>
using namespace std;

int main() {
    
    struct pollfd pfds[1];

    pfds[0].fd = 0;
    pfds[0].events = POLLIN;

    cout << "Hit return or wait for 2.5 seconds for timeout" << endl;
    int res = poll(pfds, 1, 2500); // 2.5 second

    if(res == 0) {
        cout << "Poll timeout" << endl;
    }
    else {
        int pollinHappened = pfds[0].revents & POLLIN;
        if(pollinHappened) {
            cout << "File Descriptor " << pfds[0].fd << " is ready to read" << endl;
        }
        else {
            cout << "Error: " << pfds[0].revents << endl;
        }
    }
    return 0;

}
