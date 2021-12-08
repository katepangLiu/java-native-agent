#include    <string.h>
#include    <stdlib.h>
#include    <dlfcn.h>

#include    "jni.h"
#include    <jvmti.h>

#define JNI_LIB_PREFIX "lib"
#ifdef __APPLE__
#define JNI_LIB_SUFFIX ".dylib"
#define VERSIONED_JNI_LIB_NAME(NAME, VERSION) JNI_LIB_PREFIX NAME "." VERSION JNI_LIB_SUFFIX
#else
#define JNI_LIB_SUFFIX ".so"
#define VERSIONED_JNI_LIB_NAME(NAME, VERSION) JNI_LIB_PREFIX NAME JNI_LIB_SUFFIX "." VERSION
#endif
#define JNI_LIB_NAME(NAME) JNI_LIB_PREFIX NAME JNI_LIB_SUFFIX

#ifndef ARRAY_SIZE
#	define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))
#endif

typedef jint (JNICALL *insturment_Agent_OnLoad_t)(JavaVM *vm, char *tail, void * reserved);
typedef void (JNICALL *insturment_Agent_OnUnload_t)(JavaVM *vm);

static void *handle_instrument = NULL;
static insturment_Agent_OnLoad_t insturment_Agent_OnLoad = NULL;
static insturment_Agent_OnUnload_t instrument_Agent_OnUnload = NULL;

static int checkException(JNIEnv *env) {
    if ((*env)->ExceptionCheck(env)) {
#ifdef DEBUG
        (*env)->ExceptionDescribe(env);
#endif
        (*env)->ExceptionClear(env);
        return 1;
    }
    return -1;
}

static void RegisterNatives(JNIEnv *env, char *classPath, const JNINativeMethod *methods, jint nMethods) {
    jclass clazz = (*env)->FindClass(env, classPath);
    checkException(env);
    if (clazz) {
        if ((*env)->RegisterNatives(env, clazz, methods, nMethods) < 0) {
            checkException(env);
            printf("[JNI] RegisterNatives %s fail\n", classPath);
        } else {
            printf("[JNI] Register %s Succ\n", classPath);
        }

        (*env)->DeleteLocalRef(env, clazz);
    } else {
        printf("[JNI] FindClass %s fail\n", classPath);
    }
}

jstring stringFromJNI(JNIEnv *env, jobject thiz){
    char* str = "NativeMethod_stringFromJNI";
    return (*env)->NewStringUTF(env, str );
}

static const JNINativeMethod methods_InstrumentWrapper[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (jstring*)stringFromJNI}
};

/*
Called when javacode System.load()/System.loadLibrary()
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    printf ("JNI_OnLoad \n");

    JNIEnv *env = NULL;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_1) != JNI_OK) {
        printf ("GetEnv failed \n");
        return JNI_ERR;
    }
    RegisterNatives(env, "com/pang/instrument_wrapper/InstrumentWrapper", methods_InstrumentWrapper, ARRAY_SIZE(methods_InstrumentWrapper));
    return JNI_VERSION_1_1;
}

/*
Called when load agent, before JNI_OnLoad
*/
JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *tail, void *reserved) {
    printf ("Agent_OnLoad \n");

    handle_instrument = dlopen(JNI_LIB_NAME("instrument"), RTLD_LAZY);
    if (handle_instrument == NULL) {
        printf ("error in dlopen: %s \n", dlerror());
        return JNI_ERR;
    }

    char* symbol = "Agent_OnLoad";
    insturment_Agent_OnLoad = (insturment_Agent_OnLoad_t)dlsym(handle_instrument, symbol);
    if ( insturment_Agent_OnLoad == NULL) {
        printf ("error in dlsym(%s): %s \n", symbol, dlerror());
        return JNI_ERR;
    }

    printf( "call insturment.Agent_OnLoad \n");
    jint status = insturment_Agent_OnLoad(vm, tail, reserved);
    printf( "insturment.Agent_OnLoad : %d\n", status);
    return status;
}

JNIEXPORT void JNICALL Agent_OnUnload(JavaVM *vm) {
    printf ("Agent_OnUnload \n");

    if( !handle_instrument ) {
        return;
    }
    char* symbol = "Agent_OnUnload";
    instrument_Agent_OnUnload = (insturment_Agent_OnUnload_t)dlsym(handle_instrument, symbol);
    if ( instrument_Agent_OnUnload) {
        instrument_Agent_OnUnload(vm);
    }

    dlclose(handle_instrument);
}