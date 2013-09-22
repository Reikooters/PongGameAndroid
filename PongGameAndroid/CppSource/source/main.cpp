#include <jni.h>
//#include <android/log.h>

//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "Application.h"
#include "InputManager.h"

Application* app;

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_pong_PongLib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_pong_PongLib_step(JNIEnv * env, jobject obj);

	JNIEXPORT void JNICALL Java_com_android_pong_PongLib_addPointer(JNIEnv * env, jobject obj, jint pointerId, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_android_pong_PongLib_movePointer(JNIEnv * env, jobject obj, jint pointerId, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_android_pong_PongLib_removePointer(JNIEnv * env, jobject obj, jint pointerId);
};

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	app = new Application(width, height);
}

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_step(JNIEnv * env, jobject obj)
{
    app->renderFrame();
}

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_addPointer(JNIEnv * env, jobject obj, jint pointerId, jfloat x, jfloat y)
{
	app->getInputManager()->addPointer(pointerId, x, y);
}

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_movePointer(JNIEnv * env, jobject obj, jint pointerId, jfloat x, jfloat y)
{
	app->getInputManager()->movePointer(pointerId, x, y);
}

JNIEXPORT void JNICALL Java_com_android_pong_PongLib_removePointer(JNIEnv * env, jobject obj, jint pointerId)
{
	app->getInputManager()->removePointer(pointerId);
}
