# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares the project name.

project("flam2")

# Specifies the C++ standard.

set(CMAKE_CXX_STANDARD 11)

# Specifies the OpenCV location
set(OpenCV_DIR "M:/OpenCV-android-sdk/sdk/native/jni") # Change this to your OpenCV SDK path
find_package(OpenCV REQUIRED)

# Add the native library to the project.
add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        ${OpenCV_LIBS}
        jnigraphics
        android
        media

        # Links the target library to the log library
        # specified in the find_library() call.
        ${log-lib})
