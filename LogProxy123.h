#include <string>
#include <sstream>
#include <iostream>

#define LOG1(s)	{ \
								LogProxy1 logProxy1; \
								logProxy1 << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s << std::endl; \
				}

#define LOG2(s)	{ \
								LogProxy2 logProxy; \
								logProxy << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s << std::endl; \
				}

#define LOG3(s)	{ \
								LogProxy3 logProxy; \
								logProxy << " | "  << " => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << s << std::endl; \
				}

// The most primitive implementation
class LogProxy1
{
public:
	LogProxy1()
	{

	}


	~LogProxy1()
	{
        std::cout << mStringStream.str().c_str();
	}


	std::stringstream& operator<<(const std::string& ss)
	{
		mStringStream.str(std::string());
		mStringStream << ss;
		return mStringStream;
	}

private:
	std::stringstream mStringStream;

};

// primitive implementation with static stringstream, NOT thread safe
class LogProxy2
{
public:
	LogProxy2()
	{

	}

	~LogProxy2()
	{
		std::cout << mStringStream.str().c_str();
	}

    std::stringstream& operator<<(const std::string& ss)
    {
        mStringStream.str(std::string());
        mStringStream << ss;
        return mStringStream;
    }

private:
	static std::stringstream mStringStream;
};

std::stringstream LogProxy2::mStringStream;

// primitive implementation with static stringstream AND buffering, NOT thread safe
class LogProxy3
{
public:
    LogProxy3()
    {

    }

    ~LogProxy3()
    {
        const static unsigned int maxCount = 1999;
        static unsigned int count = 0;

        if (count < maxCount)
        {
            ++count;
        }
        else
        {
            std::cout << mStringStream.str().c_str();

            count = 0;
            mStringStream.str(std::string());
            auto p = mStringStream.str().c_str();
            mStringStream.rdbuf()->pubsetbuf(new char[20024](), 20024);
        }
    }

    std::stringstream& operator<<(const std::string& ss)
    {
        mStringStream << ss;
        return mStringStream;
    }

private:
    static std::stringstream mStringStream;
};

std::stringstream LogProxy3::mStringStream;
