#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// Simple hi-res timer
// Print elapsed time when going out of scope
class Timer
{
public:	
    Timer() : m_startTime(std::chrono::high_resolution_clock::now())
    {

    }

    Timer(std::string name) : m_startTime(std::chrono::high_resolution_clock::now()), m_name(name)
    {

    }

    ~Timer()
	{
    	auto end = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double, std::milli> elapsed = end - m_startTime;
		std::cout << m_name << " Elapsed: " << elapsed.count() << " ms\n";
	}

private:
	std::chrono::_V2::system_clock::time_point  m_startTime;
    std::string m_name;
};
