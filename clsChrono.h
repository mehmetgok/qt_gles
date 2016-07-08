#if !defined(_chrono_)
#define _chrono_


#if defined(WIN64) ||  defined(_WIN32)
	#include <windows.h>	
#elif defined(__linux)
	#include <time.h>
#endif


class clsChrono
{
public:
	clsChrono();
	~clsChrono();

	int startChrono();

	double getElapsed_ms();
	double getElapsed_us();


private:
	

		#if defined(WIN64) ||  defined(_WIN32)
			
			double PCFreq;	
			__int64 CounterStart;

		#elif defined(__linux)
            struct timespec ts;
            unsigned t1, t2;

		#endif



};


#endif
