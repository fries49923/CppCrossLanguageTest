#include <jni.h>
#include <string>
#include <chrono>
#include <thread>
#include "SimpleNativeLib.h"

static JavaVM* gJvm = nullptr;
static jobject gCallbackObj01 = nullptr; // 全局引用保存 Java callback 物件
static jobject gCallbackObj02 = nullptr;

// 取得 JNIEnv
JNIEnv* getJNIEnv() {
    JNIEnv* env = nullptr;
    if (gJvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        // Attach current thread if needed
        jint ret = gJvm->AttachCurrentThread(&env, nullptr);
        if (ret != JNI_OK) {
            return nullptr;
        }
    }
    return env;
}

static MathOperations* gMathOps = nullptr;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = nullptr;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }

    // 初始化 MathOperations 結構
    gMathOps = (MathOperations*)malloc(sizeof(MathOperations));
    init_math_operations(gMathOps);

    // 其他初始化工作...

    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
    // 清理資源
    if (gMathOps) {
        free(gMathOps);
        gMathOps = nullptr;
    }
}

//-----------------------------------

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nativelib_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from nativelib C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_nativelib_NativeLib_mathOperationMultiply(
        JNIEnv* env,
        jobject /* this */,
        jint a,
        jint b) {
    return math_operation_multiply(a, b);
}

// 同步的callback
extern "C" JNIEXPORT void JNICALL
Java_com_example_nativelib_NativeLib_mathOperationAdd(
        JNIEnv* env,
        jobject thiz,
        jint a,
        jint b,
        jobject callback) {

    // 保存 JVM 指標
    if (gJvm == nullptr) {
        env->GetJavaVM(&gJvm);
    }

    // 建立全局引用保存 callback，防止被 GC
    if (gCallbackObj01 != nullptr) {
        env->DeleteGlobalRef(gCallbackObj01);
        gCallbackObj01 = nullptr;
    }
    gCallbackObj01 = env->NewGlobalRef(callback);

    // 呼叫 C++ 原生函式，傳入 callback
    // C++ callback lambda，捕捉 JNI env 與 callback 物件
    auto cppCallback = [](int result) {
        JNIEnv* env = getJNIEnv();
        if (!env || !gCallbackObj01) return;

        // 找 callback 的 onResult(int) 方法
        jclass callbackClass = env->GetObjectClass(gCallbackObj01);
        jmethodID methodId = env->GetMethodID(callbackClass, "onResult", "(I)V");
        if (methodId == nullptr) return;

        env->CallVoidMethod(gCallbackObj01, methodId, result);
    };

    math_operation_add(a, b, cppCallback);

    // callback 用完後清理
    env->DeleteGlobalRef(gCallbackObj01);
    gCallbackObj01 = nullptr;
}

// 同步的callback
extern "C" JNIEXPORT void JNICALL
Java_com_example_nativelib_NativeLib_mathOperationAddStruct(
        JNIEnv* env,
        jobject thiz,
        jobject paramsObj,
        jobject callback) {

    // 保存 JVM 指標
    if (gJvm == nullptr) {
        env->GetJavaVM(&gJvm);
    }

    // 建立全局引用保存 callback，防止被 GC
    if (gCallbackObj02 != nullptr) {
        env->DeleteGlobalRef(gCallbackObj02);
        gCallbackObj02 = nullptr;
    }
    gCallbackObj02 = env->NewGlobalRef(callback);

    // 呼叫 C++ 原生函式，傳入 callback
    // C++ callback lambda，捕捉 JNI env 與 callback 物件
    auto cppCallback = [](int result) {
        JNIEnv* env = getJNIEnv();
        if (!env || !gCallbackObj02) return;

        // 找 callback 的 onResult(int) 方法
        jclass callbackClass = env->GetObjectClass(gCallbackObj02);
        jmethodID methodId = env->GetMethodID(callbackClass, "onResult", "(I)V");
        if (methodId == nullptr) return;

        env->CallVoidMethod(gCallbackObj02, methodId, result);
    };

    jclass paramsClass = env->GetObjectClass(paramsObj);

    jfieldID aField = env->GetFieldID(paramsClass, "a", "I");
    jfieldID bField = env->GetFieldID(paramsClass, "b", "I");

    jint a = env->GetIntField(paramsObj, aField);
    jint b = env->GetIntField(paramsObj, bField);

    AddParams params = { a, b };

    // 呼叫 native 函式
    math_operation_add_struct(params, cppCallback);

    // callback 用完後清理
    env->DeleteGlobalRef(gCallbackObj02);
    gCallbackObj02 = nullptr;
}

//-----------------------------------

extern "C" JNIEXPORT jint JNICALL
Java_com_example_nativelib_NativeLib_getGlobalVariable(
        JNIEnv* env, jobject /*thiz*/) {
    return get_global_variable();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_nativelib_NativeLib_setGlobalVariable(
        JNIEnv* env, jobject /*thiz*/, jint value) {
    set_global_variable(value);
}

//-----------------------------------

// 非同步的callback
extern "C" JNIEXPORT void JNICALL
Java_com_example_nativelib_NativeLib_updateValueAsync(
        JNIEnv* env,
        jobject thiz,
        jobject callback
) {
    if (!gJvm) env->GetJavaVM(&gJvm);

    jobject callbackGlobalRef = env->NewGlobalRef(callback);

    jclass localUpdateClass = env->FindClass("com/example/nativelib/UpdateData");
    if (!localUpdateClass) return;

    jclass updateDataClass = (jclass)env->NewGlobalRef(localUpdateClass);

    std::thread([callbackGlobalRef, updateDataClass]() {
        JNIEnv* env = getJNIEnv();
        if (!env) return;

        UpdateData data;
        data.value = 0;

        update_value_after_delay(&data);

        jmethodID constructor = env->GetMethodID(updateDataClass, "<init>", "(I)V");
        if (!constructor) return;

        jobject updateDataObj = env->NewObject(updateDataClass, constructor, data.value);
        if (!updateDataObj) return;

        jclass callbackCls = env->GetObjectClass(callbackGlobalRef);
        jmethodID onResult = env->GetMethodID(callbackCls, "onResult", "(Lcom/example/nativelib/UpdateData;)V");
        if (onResult) {
            env->CallVoidMethod(callbackGlobalRef, onResult, updateDataObj);
        }

        env->DeleteGlobalRef(callbackGlobalRef);
        env->DeleteGlobalRef(updateDataClass);
    }).detach();
}

//-----------------------------------

extern "C" JNIEXPORT jint JNICALL
Java_com_example_nativelib_NativeLib_add(
        JNIEnv* env, jobject /*thiz*/, jint a, jint b) {
    if (gMathOps && gMathOps->add) {
        return gMathOps->add(a, b);
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_nativelib_NativeLib_subtract(
        JNIEnv* env, jobject /*thiz*/, jint a, jint b) {
    if (gMathOps && gMathOps->subtract) {
        return gMathOps->subtract(a, b);
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_nativelib_NativeLib_multiply(
        JNIEnv* env, jobject /*thiz*/, jint a, jint b) {
    if (gMathOps && gMathOps->multiply) {
        return gMathOps->multiply(a, b);
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_nativelib_NativeLib_divide(
        JNIEnv* env, jobject /*thiz*/, jint a, jint b) {
    if (gMathOps && gMathOps->divide) {
        return gMathOps->divide(a, b);
    }
    return 0;
}