# Flam2 - Real-Time Edge Detection Viewer

This is a minimal Android app that captures camera frames, processes them using OpenCV in C++ (via JNI), and displays the processed output using OpenGL ES. It also includes a minimal TypeScript-based web page to display a sample processed frame.

## ✅ Features Implemented

### Android
- **Camera Feed Integration**: Uses `Camera2` API with a `TextureView` to capture frames from the camera.
- **Frame Processing via OpenCV (C++)**: Each frame is sent to native C++ code using JNI. A Canny Edge Detection filter is applied using OpenCV.
- **Render Output with OpenGL ES**: The processed frame (edge-detected) is rendered as a texture using OpenGL ES 2.0.

### Web
- **Web Viewer (TypeScript)**: A minimal web page that displays a static, base64-encoded sample of a processed frame. It also shows some basic dummy stats like resolution and FPS.

## 📷 Screenshot

![App Screenshot](https://i.imgur.com/your-screenshot.png) 
*(placeholder for a screenshot of the working app)*

## ⚙️ Setup Instructions

### Prerequisites
- Android Studio
- Android NDK
- OpenCV for Android SDK (Download from [OpenCV website](https://opencv.org/releases/) and extract it)

### Steps
1. **Clone the repository:**
   ```bash
   git clone https://github.com/SomTheSheep/Flam2.git
   cd Flam2
   ```
2. **Configure OpenCV Path:**
   - Open the `app/src/main/jni/CMakeLists.txt` file.
   - Modify the `set(OpenCV_DIR "...")` line to point to the `sdk/native/jni` directory of your extracted OpenCV for Android SDK. For example:
     ```cmake
     set(OpenCV_DIR "C:/path/to/your/OpenCV-android-sdk/sdk/native/jni")
     ```
3. **Build and Run:**
   - Open the project in Android Studio.
   - Let Gradle sync and build the project.
   - Run the app on an Android device.

### Web Viewer
1. **Navigate to the web directory:**
   ```bash
   cd web
   ```
2. **Install dependencies:**
   ```bash
   npm install
   ```
3. **Build the TypeScript code:**
   ```bash
   npm run build
   ```
4. **Open `index.html` in a web browser.**

## 🧠 Quick Explanation of Architecture

### Android App
- **`MainActivity.java`**: Manages the `Camera2` API to set up the camera and capture frames. It also manages the `GLSurfaceView` for rendering.
- **`ImageReader`**: Captures frames from the camera in `YUV_420_888` format.
- **JNI (`native-lib.cpp`)**:
    - A native function `processImage(Image image)` is called from `MainActivity` for each frame.
    - The `AImage` from the Android `Image` object is converted to an OpenCV `cv::Mat`.
    - The YUV image is converted to grayscale.
    - **Canny Edge Detection** is applied to the grayscale image.
    - The resulting single-channel (grayscale) image byte array is returned to the Java side.
- **OpenGL (`gl` package)**:
    - **`MainRenderer.java`**: Implements the `GLSurfaceView.Renderer`. It orchestrates the drawing process.
    - **`TextureRenderer.java`**: Handles the OpenGL shader program, vertex buffers, and texture setup. It takes the processed frame data and renders it onto a quad that fills the screen.
- **Frame Flow**:
    1. `Camera2` captures a frame and sends it to an `ImageReader`.
    2. The `onImageAvailable` listener gets the `Image`.
    3. The `Image` is passed to the native `processImage` function via JNI.
    4. C++ code performs Canny edge detection and returns the processed `byte[]`.
    5. The `byte[]` is passed to the `MainRenderer`.
    6. `MainRenderer` updates its texture with the new frame data.
    7. `GLSurfaceView` is requested to render a new frame, and the `TextureRenderer` draws the edge-detected image.

### TypeScript Web Viewer
- **`index.html`**: A simple HTML file with an `<img>` tag to display the frame and a `<div>` for stats.
- **`index.ts`**:
    - Contains a hardcoded base64 string representing a sample processed frame.
    - It sets the `src` of the `<img>` tag to this base64 string.
    - It updates the stats `<div>` with some dummy information.
- **`tsconfig.json`**: Configures the TypeScript compiler.
- **`package.json`**: Manages dependencies (`typescript`) and provides a build script (`tsc`).
