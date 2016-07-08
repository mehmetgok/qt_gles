#include "clsChrono.h"

clsChrono::clsChrono()
{

	#if defined(WIN64) ||  defined(_WIN32)
		PCFreq = 0.0;
		CounterStart = 0;
	#elif defined(__linux)
		
	#endif

	
}


int clsChrono::startChrono()
{


	#if defined(_WIN64) ||  defined(_WIN32)

        LARGE_INTEGER li;

        // Failed to query frequency
        if(!QueryPerformanceFrequency(&li))
			return -1;

        PCFreq = double(li.QuadPart);

        QueryPerformanceCounter(&li);

        CounterStart = li.QuadPart;



	#elif defined(__linux)
        clock_gettime(CLOCK_REALTIME, &ts);
        t1 = ts.tv_sec * 1000000 + ts.tv_nsec / 1000;


	#endif

}

double clsChrono::getElapsed_ms()
{
	#if defined(_WIN64) ||  defined(_WIN32)

         LARGE_INTEGER li;
			
		// mili seconds
        PCFreq /= 1000.0;
				
        QueryPerformanceCounter(&li);
		
        return double(li.QuadPart-CounterStart)/PCFreq;

	
	#elif defined(__linux)

        clock_gettime(CLOCK_REALTIME, &ts);

        t2 = ts.tv_sec * 1000000 + ts.tv_nsec / 1000;

        return (t2-t1)/1000.0;

	#endif

}


double clsChrono::getElapsed_us()
{
#if defined(_WIN64) ||  defined(_WIN32)

        LARGE_INTEGER li;

       // mili seconds
       PCFreq /= 1000000.0;

       QueryPerformanceCounter(&li);

       return double(li.QuadPart-CounterStart)/PCFreq;


#elif defined(__linux)
    clock_gettime(CLOCK_REALTIME, &ts);

    t2 = ts.tv_sec * 1000000 + ts.tv_nsec / 1000;

    return double(t2-t1);


#endif

}

clsChrono::~clsChrono()
{
}
