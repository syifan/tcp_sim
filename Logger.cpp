#include "Scheduler.h"
#include "Logger.h"

namespace tcpsim {

Logger::Logger(const std::string &log_name) {

	// Open log file
	log_file.open(log_name);
}

Logger::~Logger() {
	log_file.close();
}


void Logger::Log(const std::string &event)
{
	log_file << Scheduler::getInstance()->getNowTime() << ", "
			<< event << "\n";
	log_file.flush();
}

} /* namespace tcpsim */
