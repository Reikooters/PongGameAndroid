#include <jni.h>
//#include <android/log.h>

//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "Application.h"

Application* app;

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_pong_PongLib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_pong_PongLib_step(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_android_pong_PongLib_mouseDown(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	app = new Application(width, height);
}

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_step(JNIEnv * env, jobject obj)
{
    app->renderFrame();
}

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_mouseDown(JNIEnv * env, jobject obj)
{
    app->touched();
}
