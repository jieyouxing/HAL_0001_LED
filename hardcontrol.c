#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>


/*
typedef struct {
	char *name;
	char *signature;
	void *fnPtr;
} JNINativeMethod;
*/

jint native_led_open(JNIEnv *env, jobject cls)
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native_led_open ...");

}

void native_led_close(JNIEnv *env, jobject cls)
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native_led_close ...");

}

jint native_led_ctrl(JNIEnv *env, jobject cls, jint which, jint status)
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native_led_ctrl: %d, %d ...", which, status);

}


static const JNINativeMethod methods[] = {
	{"ledOpen", "()I", (void *)native_led_open},
	{"ledClose", "()V", (void *)native_led_close},
	{"ledCtrl", "(II)I", (void *)native_led_ctrl},
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;
	
	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
		return JNI_ERR; /* JNI version not supported */
	}
	
	cls = (*env)->FindClass(env, "com/jie/hardlibrary/HardControl");
	
	if (cls == NULL) {
		return JNI_ERR;
	}
	
	if((*env)->RegisterNatives(env, cls, methods, sizeof(methods)/sizeof(methods[0])) < 0)
	{
		return JNI_ERR;
	}
	
	return JNI_VERSION_1_4;
}

