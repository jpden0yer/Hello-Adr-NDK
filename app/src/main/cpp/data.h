#ifndef data_h
#define data_h


#include "../../../../../../../../../AppData/Local/Android/Sdk/ndk/20.0.5594570/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/jni.h"

extern void data_init(JNIEnv* p_env, jobject p_thiz, jstring filename, unsigned long interval  );
extern bool data_poll(void);
extern jstring get_line(void);

#endif