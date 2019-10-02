



/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu-features.h>
#include <stdbool.h>
#include "helloneon-intrinsics.h"


/* return current time in milliseconds */
static double
now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}



jstring  Java_com_example_helloneon_HelloNeon_stringFromJNI( JNIEnv* env,
                                                             jobject thiz ) {

    int seconsaperline = 1;
    //JP-CF090819 put back lineno (deleted from intermediary version)
    static int lineno = 1;
    static double t0 = 0;
    if (t0 == 0) { t0 = now_ms(); }


    //JP-CF 090819 originally incorrectly used just this in place of next 2
    jclass clz = (*env)->GetObjectClass(env, thiz);

    //JP-CF 090819 added following line, passing jniHelperClz to GetMethodID:
    jclass jniHelperClz = (*env)->NewGlobalRef(env, clz);

    //JP-CF 090819 added following line, passing mainActivityObj to CallVoidMethod:
    jclass mainActivityObj = (*env)->NewGlobalRef(env, thiz);

    jmethodID timerId2 = (*env)->GetMethodID(env, jniHelperClz,
                                             "updateSign", "(Ljava/lang/String;)V");

    jstring  jstr;

    while (true) {
        if (((now_ms() - t0) * .001) >= seconsaperline) {
            t0 = now_ms();

            //JP-CF 090819 put back lineno incrementing
            lineno++ ;
            if (lineno > 10) lineno = 1;

        }

        //JP-CF090819 added following lines for looping
        if (lineno == 1) jstr = (*env)->NewStringUTF(env, "line 1");
        else if (lineno == 2) jstr = (*env)->NewStringUTF(env, "line 2");
        else if (lineno == 3) jstr = (*env)->NewStringUTF(env, "line 3");
        else if (lineno == 4) jstr = (*env)->NewStringUTF(env, "line 4");
        else if (lineno == 5) jstr = (*env)->NewStringUTF(env, "line 5");
        else if (lineno == 6) jstr = (*env)->NewStringUTF(env, "line 6");
        else if (lineno == 7) jstr = (*env)->NewStringUTF(env, "line 7");
        else if (lineno == 8) jstr = (*env)->NewStringUTF(env, "line 8");
        else if (lineno == 9) jstr = (*env)->NewStringUTF(env, "line 9");
        else if (lineno == 10) jstr = (*env)->NewStringUTF(env, "line 10");
        (*env)->CallVoidMethod(env, mainActivityObj, timerId2, jstr);
    }
    //return jstr;

}
