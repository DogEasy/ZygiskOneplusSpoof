#ifndef ONEPLUSZYGISK_HOOK_H
#define ONEPLUSZYGISK_HOOK_H


#include <jni.h>
#include <fcntl.h>
#include "zygisk.hpp"

using zygisk::Api;

class Hook {
public:
    Hook(Api *api, JNIEnv *env) {
        this->api = api;
        this->env = env;
    }

    void hook();

private:
    Api *api;
    JNIEnv *env;
};

#endif //ONEPLUSZYGISK_HOOK_H
