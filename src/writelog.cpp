#include <iostream>

/**
* A simple function for logging information
*/
void writelog(int level, std::string message) {
	std::string messages[] = {
		"[DEBUG]",
		"[MESSAGE]",
		"[INFO]",
		"[WARN]",
		"[ERROR]"
	};

	char colors[5][8] = {
		{ 0x1b, '[', '1', ';', '3', '4', 'm', 0 },
		{ 0x1b, '[', '0', ';', '3', '2', 'm', 0 },
		{ 0x1b, '[', '1', ';', '3', '3', 'm', 0 },
		{ 0x1b, '[', '0', ';', '3', '6', 'm', 0 },
		{ 0x1b, '[', '0', ';', '3', '1', 'm', 0 }
	};
	char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

	std::cout << colors[level] << messages[level] << " " << normal << message << std::endl;
}

