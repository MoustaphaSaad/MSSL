#pragma once

#include "Globals.h"
#include <sstream>
#include <unordered_map>
#include <cstdint>
#include <string>
#include "InputInterface.h"

namespace MSSL
{
	enum class LOG_LEVEL: uint8_t { COUT, LOG, ERROR };

	struct MSSL_API LogEntry
	{
		LOG_LEVEL level;
		std::string message;
		Input::Position position;
	};

	class MSSL_API Log
	{
	protected:
		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>> m_logEntries;

	public:
		static std::unordered_map<LOG_LEVEL, std::vector<LogEntry>> getLogEntries();

		static std::string getLogText();

		static void dumpLogEntriesToFile(std::string filename);

		static void log(LOG_LEVEL level, std::string message, Input::Position position);
	};
}