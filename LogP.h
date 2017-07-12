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
			using namespace LOG; \
			if(messageLevel >= LogProxy::getCurrentLevel()) \
			{ \
				LogProxy(__FILE__, __LINE__, __PRETTY_FUNCTION__) << " | "  << s; \
			} \
		}

class LogProxy
{
public:
	LogProxy(const std::string& fileName, const unsigned int lineNum, const std::string& prettyFunc)
	{

		auto now = std::chrono::system_clock::now();
		auto now_c = std::chrono::system_clock::to_time_t(now);
		mStringStream << std::put_time(std::localtime(&now_c), "%F %T");

		if(logMillisec == true)
		{
			auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			mStringStream << "." << (milli % 1000);
		}

		if(logThreadId == true)
		{
			mStringStream << " | " << pthread_self();
		}

		if(logFilename == true)
		{
			mStringStream << " | " << fileName;
		}

		if(logLinenum == true)
		{
			mStringStream << " :" << lineNum;
		}

		if(logPrettyFunc == true)
		{
			mStringStream << " | " << prettyFunc;
		}
	}

	~LogProxy()
	{
        std::cout << mStringStream.str().c_str() << std::endl << std::endl << std::endl;
	}

	std::stringstream& operator<<(const std::string& ss)
	{
		mStringStream << ss ;
		return mStringStream;
	}


	// currentLevel
	static inline LOG::logLevel getCurrentLevel()
	{
		return currentLevel;
	}

	static inline void setCurrentLevel(LOG::logLevel l)
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
	std::stringstream mStringStream;
	static LOG::logLevel currentLevel;

	static bool logMillisec;
	static bool logThreadId;
	static bool logFilename;
	static bool logLinenum;
	static bool logPrettyFunc;
};

