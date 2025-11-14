#include <jni.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <android/log.h>

#define LOG_TAG "native-lib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_somthesheep_flam2_MainActivity_processImage(
        JNIEnv* env,
        jobject /* this */,
        jobject image) {

    // This is a placeholder.
    // In a real app, you would get the image planes and process them with OpenCV.
    // For now, we just log that the function was called.
    LOGD("processImage called");
}
