package com.amb288.picasso;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRenderer implements GLSurfaceView.Renderer {

    Triangle t1;
    Triangle t2;
    Triangle t3;
    Triangle t4;
    Triangle t5;
    Triangle t6;
    Triangle t7;
    Triangle a1;
    Triangle a2;
    Triangle a3;

    Triangle b1;
    Triangle b2;
    Triangle b3;
    Triangle b4;

    Square mSquare;

    // mMVPMatrix is an abbreviation for "Model View Projection Matrix"
    private final float[] mMVPMatrix = new float[16];
    private final float[] mProjectionMatrix = new float[16];
    private final float[] mViewMatrix = new float[16];
    private final float[] mRotationMatrix = new float[16];

    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        // Set the background frame color
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // initialize a triangle

        t1 = new Triangle(3.0f / 10, 0.3f / 10, 4.4f / 10, 2.5f / 10, 2.2f / 10, 4.5f / 10, 1.0f, 0.0f, 1.0f);
        t2 = new Triangle(1.9f / 10, 2.4f / 10, 1.5f / 10, 4.9f / 10, -1.6f / 10, 4.8f / 10, 1.0f, 0.0f, 0.0f);
        t3 = new Triangle(-0.1f / 10, 3.0f / 10, -2.2f / 10, 4.3f / 10, -4.4f / 10, 2.1f / 10, 1.0f, 0.0f, 0.0f);
        t4 = new Triangle(-2.1f / 10, 2.0f / 10, -4.9f / 10, 1.3f / 10, -4.6f / 10, -1.65f / 10, 1.0f, 0.0f, 1.0f);
        t5 = new Triangle(-2.0f / 10, -4.5f / 10, -2.8f / 10, -0.1f / 10, -4.2f / 10, -2.4f / 10, 1.0f, 1.0f, 0.0f);
        t6 = new Triangle(-1.8f / 10, -2.2f / 10, -1.2f / 10, -4.9f / 10, 1.8f / 10, -4.8f / 10, 1.0f, 0.0f, 0.0f);
        t7 = new Triangle(0.4f / 10, -2.9f / 10, 2.5f / 10, -4.3f / 10, 4.6f / 10, -2.05f / 10, 1.0f, 1.0f, 0.0f);
        a1 = new Triangle(2.3f / 10, -1.9f / 10, 4.6f / 10, 1.8f / 10, 4.4f / 10, 1.0f / 10, 1.0f, 0.0f, 0.0f);
        a2 = new Triangle(4.9f / 10, -1.1f / 10, 4.6f / 10, 1.8f / 10, 4.3f / 10, 1.2f / 10, 1.0f, 1.0f, 0.0f);
        a3 = new Triangle(3.6f / 10, 0.0f / 10, 3.95f / 10, 0.6f / 10, 5.4f / 10, 0.8f / 10, 1.0f, 0.0f, 1.0f);

        b1 = new Triangle(-4.0f / 10, 4.0f / 10, 2.0f / 10, 5.0f / 10, -4.0f / 10, -5.0f / 10, 0.0f, 0.0f, 0.0f);
        b2 = new Triangle(5.0f / 10, 5.0f / 10, 4.0f / 10, 0.0f / 10, -2.0f / 10, 4.0f / 10, 0.0f, 0.0f, 0.0f);
        b3 = new Triangle(5.0f / 10, 1.0f / 10, 4.0f / 10, -4.0f / 10, -3.0f / 10, 0.0f / 10, 0.0f, 0.0f, 0.0f);
        b4 = new Triangle(-5.0f / 10, -4.0f / 10, 0.0f / 10, 4.0f / 10, 3.0f / 10, -4.0f / 10, 0.0f, 0.0f, 0.0f);

        // initialize a square
        mSquare = new Square();
    }

    public void onDrawFrame(GL10 g1) {
        float[] scratch = new float[16];

        // Redraw background color
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        g1.glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        b1.draw(g1);
        g1.glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
        b2.draw(g1);
        g1.glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        b3.draw(g1);
        g1.glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        b4.draw(g1);

        g1.glColor4f(192.0f / 255.0f, 137.0f / 255.0f, 0.0f / 255.0f, 1.0f);

        // Draw triangle
        t1.draw(g1);
        t2.draw(g1);
        t3.draw(g1);
        t3.draw(g1);
        t4.draw(g1);
        t5.draw(g1);
        t6.draw(g1);
        t7.draw(g1);

        g1.glColor4f(1f, 1f, 1f, 1f);

        a1.draw(g1);
        a2.draw(g1);
        a3.draw(g1);
    }

    public void onSurfaceChanged(GL10 g1, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
    }

}