#include <string>
#include <sstream>
#include <iostream>

#define LOG(s)	{ \
								LogProxy logProxy; \
								logProxy << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s; \
				}

#define LOGX	{ \
								LogProxy logProxy; \
								logProxy << std::this_thread::get_id() << " => " << __PRETTY_FUNCTION__ << " : " << __LINE__ << L" " << std::endl; \
				}

class LogProxy
{
public:
	LogProxy()
	{

	}


	~LogProxy()
	{
		//std::cout << mStringStream.str() << std::endl;
	}

	// std::stringstream& operator<<(const std::string& ss)
	// {
	// 	mStringStream << ss;
	// 	return mStringStream;
	// }

	std::stringstream& operator<<(const std::string& ss)
	{
		mStringStream << ss;
		return mStringStream;
	}

private:
	std::stringstream mStringStream;

};
