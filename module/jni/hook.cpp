#include "hook.h"
#include "logging.h"
#include <string>

using namespace std;

jstring (*orig_native_get)(JNIEnv *env, jclass clazz, jstring keyJ, jstring defJ);

jstring my_native_get(JNIEnv *env, jclass clazz, jstring keyJ, jstring defJ) { const char *key = env->GetStringUTFChars(keyJ, nullptr); const char *def = env->GetStringUTFChars(defJ, nullptr);

jstring hooked_result = nullptr;

if (strcmp(key, "ro.product.model") == 0) {
    hooked_result = env->NewStringUTF("PHN110");
}

env->ReleaseStringUTFChars(keyJ, key);
env->ReleaseStringUTFChars(defJ, def);

if (hooked_result != nullptr) {
    return hooked_result;
} else {
    return orig_native_get(env, clazz, keyJ, defJ);
}

}

void hookSystemProperties(JNIEnv *env, zygisk::Api *api) { LOGD("hook SystemProperties\n");

JNINativeMethod targetHookMethods[] = {
        {"native_get", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
         (void *) my_native_get},
};

api->hookJniNativeMethods(env, "android/os/SystemProperties", targetHookMethods, 1);

*(void **) &orig_native_get = targetHookMethods[0].fnPtr;

LOGD("hook SystemProperties done: %p\n", orig_native_get);

}

void Hook::hook() { hookSystemProperties(env, api); }

