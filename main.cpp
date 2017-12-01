#include "TCPServer.h"
#include "ControllerNode.h"

int main(){
    ControllerNode disksControllerNode;

    const char* a = "0101";
    const char* b = "001";
    const char* c = "1111";
    const char* d = "1";
    vector<const char*> list = {a, b, c, d};

    disksControllerNode.parity = disksControllerNode.calcParity(list);

    disksControllerNode.disksStorageUsed = {4,3,4,1};
    string bbbb = disksControllerNode.restoreWithParity(2, list);
    int aa = 1;

    //TCPServer s;
    //s.start();
}