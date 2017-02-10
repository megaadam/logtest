#include "LogProxy.h"
#include "Timer.h"
#include <unistd.h>

void func()
{
	const int repeat = 1000000;
	std::srand(std::time(0));
	auto rnd = std::rand();

	{
		printf("\nTest LOG() x %i\n", repeat);
		Timer t;
		for(int i = 0; i < repeat; ++i)
		{
			LOG("rnd: "  << rnd);	
		}
	}



	{
		printf("\nTest LOG2() x %i\n", repeat);
		Timer t;
		for(int i = 0; i < repeat; ++i)
		{
			LOG("rnd: "  << rnd);	
		}
	}



	// {
 //        printf("\nTest direct \"std::cout << \": x %i\n", repeat);
 //        Timer t;
 //        for(int i = 0; i < repeat; ++i)
 //        {
 //            std::cout << " | => " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " rnd: " << rnd << "\n";

 //        }
 //    }

	// {
	// 	printf("\nTest stringstream empty constructor: x %i\n", repeat);
	// 	Timer t;
	// 	for(int i = 0; i < repeat; ++i)
	// 	{
	// 		{
	// 			std::stringstream dummy;
	// 		}
	// 	}
	// }





	// {
	// 	printf("\nTest printf() x %i\n", repeat);
	// 	Timer t;
	// 	for(int i = 0; i < repeat; ++i)
	// 	{
	// 		printf(" | => %s:%i rnd: %i\n", __PRETTY_FUNCTION__, __LINE__, rnd);
	// 	}
	// }



}

int main()
{
	func();
}
