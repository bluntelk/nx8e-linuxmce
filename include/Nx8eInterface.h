#ifndef NX8EINTERFACE_H
#define NX8EINTERFACE_H

#include <iostream>
#include <vector>
#include <boost/asio.hpp> // include boost

using boost::asio::ip::tcp;
using namespace::boost::asio;

const uint8_t NX8E_MSG_START = 0x7E;


class Nx8eInterface
{
    public:
        enum PortType_t { serial, telnet };

        /** Default constructor */
        Nx8eInterface(PortType_t);

        /** Default destructor */
        virtual ~Nx8eInterface();


        bool setConfiguration(std::string serial_port, int serial_baud, int serial_character_size, std::string serial_flow_control, std::string serial_parity, std::string serial_end_bits);
        bool setConfiguration(std::string telnet_address, int telnet_port);

        std::vector<std::string> getZoneNames();

        void handleIncomingMessages();
    protected:
        bool connectToDataStream();
        bool addMessageToQueue(std::vector<uint8_t> message);
    private:
        PortType_t _port_type;

        // serial port variables
        std::string _serial_port;
        int _serial_baud, _serial_character_size;
        std::string _serial_end_bits, _serial_parity, _serial_flow_control ;

        // telnet connection settings
        std::string _telnet_address;
        int _telnet_port;

        boost::asio::ip::tcp::socket *_conn_telnet_socket;

        boost::asio::serial_port *_conn_serial_port;

        uint8_t readByte();
        uint8_t unstuff_byte(uint8_t this_byte, uint8_t next_byte);
        bool isMessageComplete(std::vector<uint8_t> the_buffer);
        void sendMessages();
        void processMessage(std::vector<uint8_t> message);
        void _initTelnetStream();
        void _initSerialPortStream();
};

#endif // NX8EINTERFACE_H
