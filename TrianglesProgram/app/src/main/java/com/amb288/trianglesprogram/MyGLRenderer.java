package com.amb288.trianglesprogram;



import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRenderer implements GLSurfaceView.Renderer {

    Triangle mTriangle;
    Square mSquare;

    // mMVPMatrix is an abbreviation for "Model View Projection Matrix"
    private final float[] mMVPMatrix = new float[16];
    private final float[] mProjectionMatrix = new float[16];
    private final float[] mViewMatrix = new float[16];
    private final float[] mRotationMatrix = new float[16];

    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        // Set the background frame color
        GLES20.glClearColor(255.0f, 255.0f, 0.0f, 1.0f);
        // initialize a triangle
        mTriangle = new Triangle();
        // initialize a square
        mSquare = new Square();
    }

    public void onDrawFrame(GL10 g1) {
        float[] scratch = new float[16];

        // Redraw background color
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        // Draw triangle
        mTriangle.draw(g1);

    }

    public void onSurfaceChanged(GL10 g1, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
    }

}