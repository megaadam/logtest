#pragma once

#include <pthread.h>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>


namespace LOG {
	enum logLevel
	{
		INFO = 0,
		WARNING = 1,
		DEBUG = 2,
		ERROR = 3,
	};
}

#define LOG(messageLevel, s) \
		{ \
			if(LogProxy::LogLevel::messageLevel >= LogProxy::getCurrentLevel()) \
			{ \
				LogProxy(__FILE__, __LINE__, __PRETTY_FUNCTION__) << " | "  << s; \
			} \
		}

class LogProxy
{

public:
	enum class LogLevel
	{
		INFO = 0,
		WARNING = 1,
		DEBUG = 2,
		ERROR = 3,
	};

	LogProxy(const char* fileName, const unsigned int lineNum, const char* prettyFunc);

	~LogProxy();

	std::stringstream& operator<<(const std::string& ss);


	// currentLevel
	static inline LogLevel getCurrentLevel()
	{
		return currentLevel;
	}

	static inline void setCurrentLevel(LogLevel l)
	{
		currentLevel = l;
	}


	// logMillisec
	static inline bool getLogMillisec()
	{
		return logMillisec;
	}

	static inline void setLogMillisec(bool l)
	{
		logMillisec = l;
	}


	// logThreadId
	static inline bool getlogThreadId()
	{
		return logThreadId;
	}

	static inline void setlogThreadId(bool l)
	{
		logThreadId = l;
	}


	// logFilename
	static inline bool getlogFilename()
	{
		return logFilename;
	}

	static inline void setlogFilename(bool l)
	{
		logFilename = l;
	}


	// logLinenum
	static inline bool getlogLinenum()
	{
		return logLinenum;
	}

	static inline void setlogLinenum(bool l)
	{
		logLinenum = l;
	}


	// logPrettyFunc
	static inline bool getlogPrettyFunc()
	{
		return logPrettyFunc;
	}

	static inline void setlogPrettyFunc(bool l)
	{
		logPrettyFunc = l;
	}



private:
	static std::stringstream mStringStream;
	static LogLevel currentLevel;

	static bool logMillisec;
	static bool logThreadId;
	static bool logFilename;
	static bool logLinenum;
	static bool logPrettyFunc;
	static bool logTraceID;
};

