#include <ctime>
#include <chrono>
#include <iostream>
#include <thread>


class Timer
{
public:	
	Timer(): m_startTime(std::chrono::high_resolution_clock::now())
	{
		
	}

	~Timer()
	{
    	auto end = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double, std::milli> elapsed = end - m_startTime;
		std::cout << "Elapsed: " << elapsed.count() << " ms\n";
	}


private:
	std::chrono::_V2::system_clock::time_point  m_startTime;
};