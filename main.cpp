#include <iostream>
#include <vector>
#include "writelog.hpp"
#include "Nx8eInterface.h"

using namespace std;


int main(int argc, char* argv[])
{
    if (1 == argc) {
        cout << "Usage: "<< endl;
        cout << "Telnet Mode: " << argv[0] << " <host> <port>" << endl;
        cout << "Serial Mode: " << argv[0] << " <port> <baud> <char_size> <flow_control> <parity> <stop bits>" << endl;
        cout << "  Where:" << endl;
        cout << "    flow control is one of (none, hardware, software)" << endl;
        cout << "    parity is one of (odd, even, none)" << endl ;
        cout << "    stop bits is one of (1, 1.5, 2)" << endl ;
        return 0;
    }

    Nx8eInterface *panel;

    try {
        if (3 == argc) {
            panel = new Nx8eInterface(Nx8eInterface::telnet);
            panel->setConfiguration(argv[1],atoi(argv[2]));
        } else {
            // attempt to configure a serial port connection
            panel = new Nx8eInterface(Nx8eInterface::serial);
        }




        panel->handleIncomingMessages();
    } catch (boost::system::system_error e) {
        cout << "Unable to connect. Please check details and try again." << endl;
        return 1;
    }



    delete panel;
}
