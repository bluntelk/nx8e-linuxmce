#include "Nx8eInterface.h"
#include <iostream>
#include <vector>
#include <boost/asio.hpp> // include boost
#include <boost/lexical_cast.hpp>
#include "writelog.hpp"

using boost::asio::ip::tcp;
using namespace::boost::asio;

Nx8eInterface::Nx8eInterface(PortType_t pt)
{
	//ctor
	_port_type = pt;
}

Nx8eInterface::~Nx8eInterface()
{
	//dtor
}

/**
* Handles directly connecting to the Alarm panel via the Serial Port
*/
bool Nx8eInterface::setConfiguration(
	std::string serial_port,
	int serial_baud,
	int serial_character_size,
	std::string serial_flow_control,
	std::string serial_parity,
	std::string serial_end_bits
)
{
	_serial_port = serial_port;

	_serial_baud = serial_baud;
	_serial_character_size = serial_character_size;
	_serial_flow_control = serial_flow_control;
	_serial_parity = serial_parity;
	_serial_end_bits = serial_end_bits;
	return 1;
}

/**
* Handles the setup of the telnet connection type (for ser2net style configurations)
*/
bool Nx8eInterface::setConfiguration(std::string telnet_address, int telnet_port)
{
	if (_port_type != telnet)
	{
		return 0;
	}

	_telnet_address = telnet_address;
	_telnet_port = telnet_port;
	return 1;
}

/**
* This is a high level function that gets the Zone names from the Alarm Panel
*/
std::vector<std::string> Nx8eInterface::getZoneNames()
{
	std::vector<std::string> zones;

	zones.push_back("test");
	return zones;
}

void Nx8eInterface::_initTelnetStream() {
	io_service io;
	tcp::resolver resolver(io);
	tcp::resolver::query query(_telnet_address, boost::lexical_cast<std::string>(_telnet_port));
	tcp::resolver::iterator it = resolver.resolve(query);
	tcp::resolver::iterator end;

	tcp::socket _conn_telnet_socket(io);
	boost::system::error_code error = boost::asio::error::host_not_found;
	//boost::asio::connect(_conn_telnet_socket,it); // only newer versions of boost
	writelog(LOG_DEBUG,"just before connection attempt");
	while (error && it != end)
	{
	  _conn_telnet_socket.close();
	  _conn_telnet_socket.connect(*it++, error);
	}

	if (error)
	{
		// failed to connect to port
		throw new boost::system::system_error(error);
	}
}

void Nx8eInterface::_initSerialPortStream() {
	io_service io;
	serial_port _conn_serial_port(io, _serial_port);
	_conn_serial_port.set_option(serial_port_base::baud_rate(_serial_baud));
	_conn_serial_port.set_option(serial_port_base::character_size(_serial_character_size));
	if ("hardware" == _serial_flow_control)
	{
		_conn_serial_port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::hardware));
	}
	else if ("software" == _serial_flow_control)
	{
		_conn_serial_port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::software));
	}
	else
	{
		_conn_serial_port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
	}

	if ("odd" == _serial_parity)
	{
		_conn_serial_port.set_option(serial_port_base::parity(serial_port_base::parity::odd));
	}
	else if ("even" == _serial_parity)
	{
		_conn_serial_port.set_option(serial_port_base::parity(serial_port_base::parity::even));
	}
	else
	{
		_conn_serial_port.set_option(serial_port_base::parity(serial_port_base::parity::none));
	}

	if ("1" == _serial_end_bits)
	{
		_conn_serial_port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
	}
	else if ("1.5" == _serial_end_bits)
	{
		_conn_serial_port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::onepointfive));
	}
	else if ("2" == _serial_end_bits)
	{
		_conn_serial_port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::two));
	}
}


/**
* Handles the I/O setup for connecting to each of our supported data streams
*/
bool Nx8eInterface::connectToDataStream()
{
	// here we make a connection to our data stream
	switch (_port_type)
	{
		// telnet connection handler
		case Nx8eInterface::telnet:
            writelog(LOG_DEBUG, "About to connect to telnet stream");
			_initTelnetStream();
			break;

		// serial port interface
		case Nx8eInterface::serial:
            writelog(LOG_DEBUG, "About to connect to serial port");
			_initSerialPortStream();
			break;
		default:
			break;
	}
	return 0;
}


/**
* Adds a message to be sent to the Alarm panel to the queue to be sent.
*/
bool Nx8eInterface::addMessageToQueue(std::vector<uint8_t> message)
{
	return 0;
}

/**
* Determines whether or not a message from the Alarm Panel is complete.
*/
bool Nx8eInterface::isMessageComplete(std::vector<uint8_t> the_buffer)
{
	bool is_complete = true;
	// the first char is the message length


	return is_complete;
}

/**
* handles sending a message
*/
void Nx8eInterface::sendMessages() {}

/**
* handles the processing of all messages from the Alarm Panel
*/
void Nx8eInterface::processMessage(std::vector<uint8_t> message) {}

/**
* Handles the reading of a single byte from the connection.
*/
uint8_t Nx8eInterface::readByte()
{
	//boost::system::error_code error;
	uint8_t the_byte;
	switch (_port_type)
	{
	case Nx8eInterface::serial:
		the_byte = 0x00;
		break;

	case Nx8eInterface::telnet:
		// read a byte from the telnet connection
        _conn_telnet_socket->read_some(boost::asio::buffer(&the_byte,1));
		break;
	}
	return the_byte;
}

/**
* Takes care of unstuffing bytes from the serial port
*/
uint8_t Nx8eInterface::unstuff_byte(uint8_t this_byte, uint8_t next_byte) {
	if ((0x7d == this_byte) && (0x5e == next_byte)) {
		return 0x7e;
	}
	if (0x7d == this_byte) {
		if (0x5d == next_byte) {
			return 0x7d;
		} else {
			return next_byte ^ 0x20;
		}
	}
	return this_byte;
}

/**
* Handles the control for communicating with the alarm panel.
*/
void Nx8eInterface::handleIncomingMessages()
{
    writelog(LOG_DEBUG,"About to connect to data stream");
	connectToDataStream();
	std::vector<uint8_t> the_buffer;
	uint8_t the_byte,next_byte,message_length,length_counter;

	while (1)
	{
		// handle any control messages - like quitting this loop

		// read data from socket and push it onto our message buffer
        the_byte = readByte();


		// if we do not get the start of the message, continue on.
		if (NX8E_MSG_START != the_byte)
		{
			continue;
		}
            writelog(LOG_DEBUG, "Starting new message");

		message_length = readByte();
		the_buffer.push_back(message_length);
		length_counter = 0;
		while (length_counter < message_length) {
			the_byte = readByte();
			// is this a stuffed byte?
			if ( (0x7e == the_byte) || (0x7d == the_byte)) {
				next_byte = readByte();
				the_byte = unstuff_byte(the_byte,next_byte);
			}
			the_buffer.push_back(the_byte);
		}

		writelog(LOG_DEBUG,"Finished Reading Message");

		// ensure we have a good message
		if (isMessageComplete(the_buffer))
		{
			// dispatch the message
			processMessage(the_buffer);

		}
		else
		{
			// we got a busted message! Log it

		}

		// clear the buffer
		the_buffer.clear();

		// and now send the next message we have queued.
		sendMessages();
	}
}
