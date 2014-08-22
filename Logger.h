#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>

namespace tcpsim {

class Logger {

	// Log file out stream
	std::ofstream log_file;

public:

	/// Constructor
	Logger(const std::string &log_name);

	/// Destructor
	virtual ~Logger();

	/// Log an event
	void Log(const std::string &event);
};

} /* namespace tcpsim */

#endif /* LOGGER_H_ */
