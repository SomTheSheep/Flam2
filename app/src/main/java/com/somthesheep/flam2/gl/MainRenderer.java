package com.somthesheep.flam2.gl;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainRenderer implements GLSurfaceView.Renderer {

    private TextureRenderer textureRenderer;
    private final Context context;
    private byte[] processedFrame;
    private int frameWidth;
    private int frameHeight;

    public MainRenderer(Context context) {
        this.context = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        textureRenderer = new TextureRenderer(context);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
        if (textureRenderer != null && processedFrame != null) {
            textureRenderer.draw(processedFrame, frameWidth, frameHeight);
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        gl.glViewport(0, 0, width, height);
    }

    public void updateFrame(byte[] frame, int width, int height) {
        this.processedFrame = frame;
        this.frameWidth = width;
        this.frameHeight = height;
    }
}
