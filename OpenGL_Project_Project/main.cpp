//
//  main.cpp
//  OpenGL_Project_Project
//
//  Created by Albany Patriawan on 7/13/24.
//


#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main(int argc, const char * argv[]) {
    
    std::cout << "Hello, World!\n";
    
    // Initialize GLFW
    glfwInit();
    
    if(!glfwInit()){
        std::cout << "failed to init!" << std::endl;
//        TRACELOG(LOG_WARNING, "GLFW: Failed to initialize GLFW");
        return -1;
    }
    
    // Specifies that we want version 3.3 of GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Set the profile of GLFW to the core profile, which gives us modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // A rectangle
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    };
    
    // Creates a window
    GLFWwindow* window = glfwCreateWindow(800, 800, "First OpenGL Project!", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "open gl window!" << std::endl;
    }
    
    
    // Add the window to the current context (presumably for handling state)
    glfwMakeContextCurrent(window);
    
    // Configures OpenGL
    gladLoadGL();
    
    // Specify the view port of OpenGL
    glViewport(0,0,800,800);
    
    
    // VERTEX SHADER
    
    // Create a shader object of type veretx shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Replaces the source code of the vertex object with the shader source
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compiles the src code of a shader
    glCompileShader(vertexShader);
    
    
    // FRAGMENT SHADER
    
    // Create a shader object of type veretx shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Replaces the source code of the vertex object with the shader source
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compiles the src code of a shader
    glCompileShader(fragmentShader);
    
    
    // SHADER PROGRAM
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // Disassemble
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    GLuint VAO; // Vertex Array Object -- used to switch between and read VBOs
    GLuint VBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); // generate 1 buffer being the VBO
    
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer
    

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Put vertices into buffer
    
    // Specifies how to read the vertices (each vertex is made of floats and is read 3 vertices at a time)
    // 0 is the index of the attribute
    int vertexSize = 3;
    glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    // Swap front and back buffer
    glfwSwapBuffers(window);
    
    while (!glfwWindowShouldClose(window)) {
        // Specify the color of background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Cleans back buffer and assigns the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        
        // Take care of GLFW events
        glfwPollEvents();
        
    }

    
    // Disassemble
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
