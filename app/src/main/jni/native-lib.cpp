#include <jni.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <android/log.h>
#include <android/media/Image.h>

#define LOG_TAG "native-lib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_somthesheep_flam2_MainActivity_processImage(
        JNIEnv* env,
        jobject /* this */,
        jobject image) {

    AImage* aImage = nullptr;
    media_status_t status = AImage_createFromJavaSurface(env, image, &aImage);
    if (status != AMEDIA_OK) {
        LOGD("Error creating AImage");
        return nullptr;
    }

    int32_t width, height;
    AImage_getWidth(aImage, &width);
    AImage_getHeight(aImage, &height);

    AImagePlane* yPlane, *uPlane, *vPlane;
    int32_t yStride, uStride, vStride;
    uint8_t *yPixel, *uPixel, *vPixel;
    int32_yLen, uLen, vLen;

    AImage_getPlanePixelStride(aImage, 0, &yStride);
    AImage_getPlanePixelStride(aImage, 1, &uStride);
    AImage_getPlanePixelStride(aImage, 2, &vStride);

    AImage_getPlaneData(aImage, 0, &yPixel, &yLen);
    AImage_getPlaneData(aImage, 1, &uPixel, &uLen);
    AImage_getPlaneData(aImage, 2, &vPixel, &vLen);

    cv::Mat yuv(height + height / 2, width, CV_8UC1);
    memcpy(yuv.data, yPixel, yLen);
    memcpy(yuv.data + yLen, uPixel, uLen);
    memcpy(yuv.data + yLen + uLen, vPixel, vLen);

    cv::Mat gray;
    cv::cvtColor(yuv, gray, cv::COLOR_YUV2GRAY_I420);

    cv::Mat edges;
    cv::Canny(gray, edges, 100, 200);

    jbyteArray result = env->NewByteArray(edges.total());
    env->SetByteArrayRegion(result, 0, edges.total(), reinterpret_cast<jbyte*>(edges.data));

    AImage_delete(aImage);

    return result;
}