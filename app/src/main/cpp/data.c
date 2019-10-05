#include "global_includes.h"
#include<stdio.h>
#include <stdbool.h>

#define  linelenght 24
#define  linecount 10

static jstring lines [linecount];
static int selected_line = 0;
char thisline [linelenght + 1];
JNIEnv* env;
jobject thiz;
jclass mainActivityObj;
jmethodID timerId2;

void data_init(JNIEnv* p_env, jobject p_thiz, jstring filename, unsigned long interval  ) {
    env = p_env;
    thiz = p_thiz;
    //JP-CF 090819 originally incorrectly used just this in place of next 2
    jclass clz = (*env)->GetObjectClass(env, thiz);
    //JP-CF 090819 added following line, passing jniHelperClz to GetMethodID:
    jclass jniHelperClz = (*env)->NewGlobalRef(env, clz);
    //JP-CF 090819 added following line, passing mainActivityObj to CallVoidMethod:
    mainActivityObj = (*env)->NewGlobalRef(env, thiz);
    timerId2 = (*env)->GetMethodID(env, jniHelperClz,
                                   "updateSign", "(Ljava/lang/String;)V");
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp)
    {
        for (int i = 1 ; i < 10; i++){
            size_t char_byte_size = 1;
            size_t char_count = 10;
            fread(&thisline, char_byte_size, char_count, fp);
            lines [i] =    (*env)->NewStringUTF(env, (const char*) &thisline);
        }
    }
    else {
        lines[0] = (*env)->NewStringUTF(env, "Pine 1");
        lines[1] = (*env)->NewStringUTF(env, "Pine 2");
        lines[2] = (*env)->NewStringUTF(env, "Pine 3");
        lines[3] = (*env)->NewStringUTF(env, "Pine 4");
        lines[4] = (*env)->NewStringUTF(env, "Pine 5");
        lines[5] = (*env)->NewStringUTF(env, "Pine 6");
        lines[6] = (*env)->NewStringUTF(env, "Pine 7");
        lines[7] = (*env)->NewStringUTF(env, "Pine 8");
        lines[8] = (*env)->NewStringUTF(env, "Pine 9");
        lines[9] = (*env)->NewStringUTF(env, "Pine 10");
    }
    tmr_init(interval);
}

bool data_poll(void){

    if (tmr_poll() )  {

        selected_line  = selected_line + 1;
        if (selected_line >= 10 )
            selected_line = 1;

        (*env)->CallVoidMethod(env, mainActivityObj, timerId2, get_line());

        return true;
    }
    return false;
}

jstring get_line(void){
    return lines[selected_line];
}