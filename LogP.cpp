#include "LogP.h"

	LogProxy::LogProxy(const char* fileName, const unsigned int lineNum, const char* prettyFunc)
	{

		auto now = std::chrono::system_clock::now();
		auto now_c = std::chrono::system_clock::to_time_t(now);
		mStringStream << std::put_time(std::localtime(&now_c), "%F %T");

		if(logMillisec == true)
		{
			auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			mStringStream << "." << std::setw(3) << std::setfill('0') << (milli % 1000);
		}

		if(logThreadId == true)
		{
			mStringStream << " | " << std::hex  << (pthread_self() & 0x0fffffffffff) << std::dec;
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

	LogProxy::~LogProxy()
	{
		// Of course the log target should be configurable to:
		// stdout, stderr, logd etc
        std::cout << mStringStream.str().c_str() << std::endl;
	}

	std::stringstream& LogProxy::operator<<(const std::string& ss)
	{
		mStringStream << ss ;
		return mStringStream;
	}

// Log level and log fields should be picked up from config
LogProxy::LogLevel LogProxy::currentLevel = LogProxy::LogLevel::ERROR;

bool LogProxy::logMillisec = true;
bool LogProxy::logThreadId = true;
bool LogProxy::logFilename = false;
bool LogProxy::logLinenum = false;
bool LogProxy::logPrettyFunc = true;

bool LogProxy::logTraceID = false; // should be true when implemented!!
