#include <jni.h>
#include "Engine.h"
#include <string>


////////////////////////////////////////////
GameEngine::Engine *mEngine;
////////////////////////////////////////////
extern "C"
JNIEXPORT void JNICALL
Java_app1_gdev_com_sample1_JDraw_on_1draw_1frame__FF(JNIEnv *env, jclass type, jfloat fTimeDtMS,
                                                     jfloat fTimeGlobalMS) {

    mEngine->Draw(fTimeDtMS, fTimeGlobalMS);
}

extern "C"
JNIEXPORT void JNICALL
Java_app1_gdev_com_sample1_JDraw_on_1surface_1changed(JNIEnv *env, jclass type, jint width,
                                                      jint height) {

    mEngine->Resize(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_app1_gdev_com_sample1_JDraw_on_1surface_1created(JNIEnv *env, jclass type) {

    mEngine = new GameEngine::Engine();
}

/*
extern "C"
jstring
Java_app1_gdev_com_sample1_MainActivity_stringFromJNI(
        JNIEnv *env,
       jobject /-* this *-/) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}*/
