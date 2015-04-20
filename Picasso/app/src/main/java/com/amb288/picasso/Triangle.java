package com.amb288.picasso;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLES20;

public class Triangle {

    private FloatBuffer vertexBuffer;
    private ByteBuffer indexBuffer;    // Buffer for index-array

    private final int mProgram;
    private int mPositionHandle;
    private int mColorHandle;
    private int vertexStride;
    private int vertexCount;
    private int mMVPMatrixHandle;

    private final String vertexShaderCode =
            "attribute vec4 vPosition;" +
                    "void main() {" +
                    "  gl_Position = vPosition;" +
                    "}";

    private final String fragmentShaderCode =
            "precision mediump float;" +
                    "uniform vec4 vColor;" +
                    "void main() {" +
                    "  gl_FragColor = vColor;" +
                    "}";

    // number of coordinates per vertex in this array
    static final int COORDS_PER_VERTEX = 3;
    float triangleCoords[] = {   // in counterclockwise order:
            0.0f,  0.622008459f, 0.0f,
            -0.5f, -0.311004243f, 0.0f,
            0.5f, -0.311004243f, 0.0f
    };

    private byte[] indices = { 0, 1, 2 }; // Indices to above vertices (in CCW)

    // Set color with red, green, blue and alpha (opacity) values
    float color[] = { 0.63671875f, 0.76953125f, 0.22265625f, 0.0f };

    public Triangle(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
        triangleCoords[0] = a;
        triangleCoords[1] = b;
        triangleCoords[2] = 0.0f;
        triangleCoords[3] = c;
        triangleCoords[4] = d;
        triangleCoords[5] = 0.0f;
        triangleCoords[6] = e;
        triangleCoords[7] = f;
        triangleCoords[8] = 0.0f;
        color[0] = g;
        color[1] = h;
        color[2] = i;
        color[3] = 1.0f;

        // initialize vertex byte buffer for shape coordinates
        ByteBuffer bb = ByteBuffer.allocateDirect(
                // (number of coordinate values * 4 bytes per float)
                triangleCoords.length * 4);
        // use the device hardware's native byte order
        bb.order(ByteOrder.nativeOrder());

        // create a floating point buffer from the ByteBuffer
        vertexBuffer = bb.asFloatBuffer();
        // add the coordinates to the FloatBuffer
        vertexBuffer.put(triangleCoords);
        // set the buffer to read the first coordinate
        vertexBuffer.position(0);

        // Setup index-array buffer. Indices in byte.
        indexBuffer = ByteBuffer.allocateDirect(indices.length);
        indexBuffer.put(indices);
        indexBuffer.position(0);

        int vertexShader = loadShader(GLES20.GL_VERTEX_SHADER, vertexShaderCode);
        int fragmentShader = loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentShaderCode);

        mProgram = GLES20.glCreateProgram();             // create empty OpenGL ES Program
        GLES20.glAttachShader(mProgram, vertexShader);   // add the vertex shader to program
        GLES20.glAttachShader(mProgram, fragmentShader); // add the fragment shader to program
        GLES20.glLinkProgram(mProgram);                  // creates OpenGL ES program executables
    }

    public static int loadShader(int type, String shaderCode){

        // create a vertex shader type (GLES20.GL_VERTEX_SHADER)
        // or a fragment shader type (GLES20.GL_FRAGMENT_SHADER)
        int shader = GLES20.glCreateShader(type);

        // add the source code to the shader and compile it
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);

        return shader;
    }

    public void draw(GL10 gl) {
        // Enable vertex-array and define the buffers
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
        gl.glVertexPointer(3, GL10.GL_FLOAT, 0, vertexBuffer);

        // Draw the primitives via index-array
        gl.glDrawElements(GL10.GL_TRIANGLES, indices.length, GL10.GL_UNSIGNED_BYTE, indexBuffer);
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
    }


    public void draw() {

    }
}
