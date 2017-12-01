#include "TCPServer.h"

int main(){
    TCPServer s;
    s.start(8080);

    json a = {};
    if (a.is_null()){
        int c  = 1;
    }
    else{
        int b = 2;
    }
}