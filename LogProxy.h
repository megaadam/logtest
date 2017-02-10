#include <string>
#include <sstream>
#include <iostream>

#define LOG(s)	{ \
								LogProxy logProxy; \
								logProxy << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s << std::endl; \
				}

#define LOG2(s)	{ \
								LogProxy2 logProxy; \
								logProxy << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s << std::endl; \
				}


class LogProxy
{
public:
	LogProxy()
	{

	}


	~LogProxy()
	{
		//std::cout << mStringStream.str().c_str() << std::endl; // #1
		printf(mStringStream.str().c_str()); // #2
	}


	std::stringstream& operator<<(const std::string& ss)
	{
		mStringStream.clear();
		mStringStream.str(std::string());
		mStringStream << ss;
		return mStringStream;
	}

private:
	static std::stringstream mStringStream;

};

std::stringstream LogProxy::mStringStream;

class LogProxy2
{
public:
	LogProxy2()
	{

	}


	~LogProxy2()
	{
		std::cout << mStringStream.str().c_str() << std::endl; // #1
		//printf(mStringStream.str().c_str()); // #2
	}


	std::stringstream& operator<<(const std::string& ss)
	{
		mStringStream.clear();
		mStringStream.str(std::string());
		mStringStream << ss;
		return mStringStream;
	}

private:
	static std::stringstream mStringStream;

};

std::stringstream LogProxy2::mStringStream;