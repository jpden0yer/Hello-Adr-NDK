//JP-CMF 071313:
//port code to raspberry pi
// no longer USE A timmer to drive spi poll (see notes in spi .c).
// we now use the number of msec since our timmer
//is initialized for our timming functionality


#include "global_includes.h"
#ifdef android_native

#include <time.h>
//#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/time.h"

#endif

unsigned long long  timer0;
unsigned long interval;

static double
now_ms(void)
{
#ifdef android_native
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
#endif
#ifdef rasp_pi_linux
    struct timeval tv;
	gettimeofday(&tv, NULL);
	return (unsigned long long)(tv.tv_sec) * 1000 +
    	(	unsigned long long)(tv.tv_usec) / 1000;
#endif


}

// tmr_init
void	tmr_init( unsigned long p_interval)
{

    timer0 = now_ms();
    interval = p_interval * 1000.0;
}

bool tmr_poll(void){

    if ((now_ms() - timer0) >= interval ){
        timer0 = timer0 + interval;
        return true;
    }
    else {
        return false;
    }


}