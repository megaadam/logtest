#include <unistd.h>
#include <memory>
#include <random>
#include <thread>

#include "LogProxy.h"
#include "LogProxy123.h"
#include "Timer.h"

void LogPerfTest()
{
	const int repeat = 4;
	const int loopCount = 25000;

	{
		Timer timerTot("LOG perf total"); // class Timer logs elapsed lifetime in destructor
		for(int i = 0; i < repeat; ++i)
		{
			auto rnd = std::rand();
			Timer timer("LOG perf");
			for(int i = 0; i < loopCount; ++i)
			{
				LOG(ERROR, "Log some random value: " << rnd);
			}
		}

	}
}

// Compare logger overhead
// Typically test with: $ ./logtest | grep total
void LogPerfTestOld()
{
	const int repeat = 4;
	const int loopCount = 25000;

	std::srand(std::time(0));
	auto rnd = std::rand();

    std::unique_ptr<Timer> p(new Timer("LOG1 total"));
    for (auto i = 0; i < repeat; ++i)
    {
        Timer t("Test LOG1() with class LogProxy ");
        for (int i = 0; i < loopCount; ++i)
        {
            LOG1("LOG1 rnd: " << rnd);
        }
    }

    p.reset(new Timer("LOG2 total"));
    for (auto i = 0; i < repeat; ++i)
    {
        Timer t("Test LOG2() with class LogProxy2 ");
        for (int i = 0; i < loopCount; ++i)
        {
            LOG2("LOG2 rnd: " << rnd);
        }
    }

    p.reset(new Timer("LOG3 total"));
    for(auto i = 0; i < repeat; ++i)
    {
        Timer t("Test LOG3() with class LogProxy3 ");
        for (int i = 0; i < loopCount; ++i)
        {
            LOG3("LOG3 rnd: " << rnd);
        }
    }

    p.reset(new Timer("printf total"));
    for (auto i = 0; i < repeat; ++i)
	 {
	 	Timer t("Simple printf()");
	 	for(int i = 0; i < loopCount; ++i)
	 	{
	 		printf(" | => %s:%i printf rnd: %i\n", __PRETTY_FUNCTION__, __LINE__, rnd);
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

class MessageProcessor
{
public:
	MessageProcessor()
	{
	}

	virtual ~MessageProcessor()
	{
		mThread.join();
	}

	void SendMessage()
	{
		static int count = 0;
		LOG(DEBUG, "Sending Stuff! " << count << " number of times");
		++count;
	}

	void ReceiveMessageMessage()
	{
		static int count = 2;
		LOG(DEBUG, "count: " << count << " => Receiving Stuff!");
		++count;
	}

	void ProcessingMessageMessage()
	{
		static int count = 1024;
		LOG(DEBUG,  "Processing # " << std::hex << std::rand());
		++count;
	}

	void Run()
	{
		auto seed = (long)this; // What other way to seed uniquely?
		std::srand(seed);

		LOG(DEBUG, "Seed: " << seed);

		for(int i = 0; i < 5; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(20 + std::rand() % 1000));
			switch(std::rand() % 3)
			{
			case 0:
				SendMessage();
				break;
			case 1:
				ReceiveMessageMessage();
				break;

			case 2:
				ProcessingMessageMessage();
				break;
			}
		}
	}


private:
	std::thread mThread  = std::thread(&MessageProcessor::Run, this); // Header file init yay!!

};

class StreamEvent
{
public:
	StreamEvent()
	{
	}

	~StreamEvent()
	{
		mThread.join();
	}

	void StreamFail()
	{
		static int count = 0;
		LOG(ERROR, "Network error count: " << count << ". Retrying...");
		++count;
	}

	void StartStream()
	{
		static int count = 1024;
		LOG(DEBUG, "count: " << count << " => Receiving Stuff!");
		++count;
	}

	void EndStream()
	{
		LOG(DEBUG,  "Transaction ID # " << std::hex << (std::rand() & 0xffff));
	}

	void Run()
	{
		auto seed = (long)this; // What other way to seed uniquely?
		LOG(DEBUG, "Seed: " << seed);

		std::srand(seed);
		for(int i = 0; i < 5; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(20 + std::rand() % 1000));
			switch(std::rand() % 3)
			{
			case 0:
				StreamFail();
				break;
			case 1:
				StartStream();
				break;

			case 2:
				EndStream();
				break;
			}
		}

	}

	private:
		std::thread mThread  = std::thread(&StreamEvent::Run, this);

};

void LogTest()
{
	LOG(DEBUG, "Forty-two equals: " << 42);
	LOG(INFO, "ALL MEDIA IS FAKE: " << 666); // Some messages should stay below the noise

	LogProxy::setCurrentLevel(LogProxy::LogLevel::DEBUG);

	LOG(DEBUG, "Forty-two equals: " << 42);
	LOG(INFO, "ALL MEDIA IS FAKE: " << 666);
	
	// Self-contained objects with individual treads
	MessageProcessor mp[2];
	StreamEvent se[2];
}

int main()
{
	LOG(ERROR, "42 hex formatted is: " << std::hex << 42);
	LOG(ERROR, "42 unformatted is: " << 42 << " ... which shows that stream formatting is restored between log lines");
	LogPerfTest();
	LogPerfTestOld();
}

