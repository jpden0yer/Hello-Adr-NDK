//JP-CMF 071313:
//port code to raspberry pi
// no longer USE A timmer to drive spi poll (see notes in spi .c).
// we now use the number of msec since our timmer
//is initialized for our timming functionality


#include "global_includes.h"
#ifdef android_native

#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/time.h"
#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/linux/time.h"
#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/lib64/clang/8.0.7/include/stdbool.h"
#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/lib64/clang/8.0.7/include/stdbool.h"
#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/time.h"
#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/linux/time.h"

#endif

#ifdef rasp_pi_linux
#include <time.h>
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
/*
unsigned long tmr_get_elsapsed_time(void)
{

	unsigned long long curr_time =
            now_ms();
	unsigned long long timer_value = curr_time - timer0;
        //timer_value is implicitly truncated from 2-long to long
	//this should be fine because the amount of time since sign started
	//is much less then the time since Jan 1 1970
	return( timer_value);  //return msec??
}
*/

bool tmr_poll(void){

    if ((now_ms() - timer0) >= interval ){
        timer0 = timer0 + interval;
        return true;
    }
    else {
        return false;
    }


}