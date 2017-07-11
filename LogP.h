#pragma once

#include <string>
#include <sstream>
#include <iostream>
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
				LogProxy logProxy; \
				logProxy << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s << std::endl; \
			} \
		}

class LogProxy
{
public:
	LogProxy()
	{

	}

	~LogProxy()
	{
        std::cout << mStringStream.str().c_str();
	}

	std::stringstream& operator<<(const std::string& ss)
	{
		mStringStream.clear();
		mStringStream.str(std::string());
		mStringStream << ss;
		return mStringStream;
	}

	static LOG::logLevel getCurrentLevel()
	{
		return currentLevel;
	}

	static void setCurrentLevel(LOG::logLevel l)
	{
		currentLevel = l;
	}

private:
	std::stringstream mStringStream;
	static LOG::logLevel currentLevel;
};

