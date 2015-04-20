package com.amb288.picasso;

import android.opengl.GLSurfaceView;
import android.content.Context;

class MyGLSurfaceView extends GLSurfaceView {

    public MyGLSurfaceView(Context context){
        super(context);

        //setEGLContextClientVersion(1);
        //super.setEGLConfigChooser(8, 8, 8, 8, 16, 0);

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(new MyGLRenderer());
    }
}