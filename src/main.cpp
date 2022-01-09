#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv[]) {
    using namespace std;

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (gl3wInit()) {
        cerr <<  "Failed to initialize OpenGL" << endl;
        return -1;
    }

    if (!gl3wIsSupported(3, 2)) {
        cerr <<  "OpenGL 3.2 not supported" << endl;

        return -1;
    }

    cout << "OpenGL" << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
