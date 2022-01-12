#include <iostream>
#include <filesystem>

#include "vgl.h"
#include "LoadShaders.h"


enum VAO_IDs {
    Triangles,
    NumVAOs // This must be the last value of the enum
};

enum Buffer_IDs {
    ArrayBuffer,
    NumBuffers // This must be the last value of the enum
};

enum Attrib_IDs {
    vPosition = 0
};

// Eww global variables
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init() {
    static const GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}
    };

    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "shaders/triangles.vert"},
            {GL_FRAGMENT_SHADER, "shaders/triangles.frag"},
            {GL_NONE,            nullptr}
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void display() {
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

int main(int argc, char *argv[]) {
    using namespace std;

    cout << "Current path: " << filesystem::current_path() << endl;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(640, 480, "Triangles", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (gl3wInit()) {
        cerr << "Failed to initialize OpenGL" << endl;
        return -1;
    }

    if (!gl3wIsSupported(3, 2)) {
        cerr << "OpenGL 3.2 not supported" << endl;

        return -1;
    }

    cout << "OpenGL" << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION);

    cout.flush();

    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render */
        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
