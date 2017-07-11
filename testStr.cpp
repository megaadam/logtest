#include "LogProxy.h"
#include "LogP.h"
#include "Timer.h"
#include <unistd.h>
#include <memory>

// Compare logger overhead
// Typically test with: $ ./logtest | grep total
void LogPerfTest()
{
	const int repeat = 100000;
	std::srand(std::time(0));
	auto rnd = std::rand();

    std::unique_ptr<Timer> p(new Timer("LOG1 total"));
    for (auto i = 0; i < 4; ++i)
    {
        Timer t("Test LOG1() with class LogProxy ");
        for (int i = 0; i < repeat; ++i)
        {
            LOG1("LOG1 rnd: " << rnd);
        }
    }

    p.reset(new Timer("LOG2 total"));
    for (auto i = 0; i < 4; ++i)
    {
        Timer t("Test LOG2() with class LogProxy2 ");
        for (int i = 0; i < repeat; ++i)
        {
            LOG2("LOG2 rnd: " << rnd);
        }
    }

    p.reset(new Timer("LOG3 total"));
    for(auto i = 0; i < 4; ++i)
    {
        Timer t("Test LOG3() with class LogProxy3 ");
        for (int i = 0; i < repeat; ++i)
        {
            LOG3("LOG3 rnd: " << rnd);
        }
    }

    p.reset(new Timer("printf total"));
    for (auto i = 0; i < 4; ++i)
	 {
	 	Timer t("Simple printf()");
	 	for(int i = 0; i < repeat; ++i)
	 	{
	 		printf(" | => %s:%i prin rnd: %i\n", __PRETTY_FUNCTION__, __LINE__, rnd);
	 	}
	 }
    p.reset(nullptr);



}

void f2()
{	// Forget these dinosauric tests
    std::ostringstream ss;
    ss << "Hello stringstream" << std::endl;
    std::cout << ss.str().c_str();
    //ss.rdbuf()->pubseekoff(0, std::ios_base::in | std::ios_base::out);
    //ss.rdbuf()->pubseekpos(0, std::ios_base::in );
    //ss.rdbuf()->pubseekpos(0, std::ios_base::out);
    //ss.rdbuf()->pubsync();
    //ss.clear();
    //ss.seekp(0); // for outputs: seek put ptr to start
    //ss.seekg(0); // for inputs: seek get ptr to start
    //ss << std::ends;

    ss.rdbuf()->pubsetbuf(new char[1024](), 1024);

    ss << "zzz" << std::endl;
    ss << "qqq" << std::endl;
    std::cout << ss.str().c_str();
    std::cout << ss.str().capacity() << std::endl;

}

void LogTest()
{
	LOG(DEBUG, "Forty-two equals: " << 42);
	LOG(INFO, "All Media Is Fake: " << 666);

	LogProxy::setCurrentLevel(LOG::DEBUG);

	LOG(DEBUG, "Forty-two equals: " << 42);
	LOG(INFO, "All Media Is Fake: " << 666);
}

int main()
{
	LogTest();
}

