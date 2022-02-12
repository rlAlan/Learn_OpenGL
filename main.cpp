#include "Libs/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


const char* vertexShaderSource{
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "gl_Position = vec4(aPos.x,aPos.y, aPos.z, 1.0);\n"
    "}\0"
};


const char* fragmentShaderSource{
    "#version 460 core\n"
    "out vec4 FragColour;\n"
    "void main(){\n"
    "FragColour= vec4(0.3, 0.2,0.5,1.0);\n"
    "}\0"
};


void frameWindow_callback(GLFWwindow* window, int width, int height);

int main()
{
    if(!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window{glfwCreateWindow(1200, 880, "WINDOW", nullptr, nullptr)};
    if(window == nullptr){
        std::cout << "COULD NOT CREATE WINDOW\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "COULD NOT LOAD GLAD\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,1200,880);
    glfwSetWindowSizeCallback(window, frameWindow_callback);


    int success;
    char infoLog[512];

    unsigned int vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n"
            << infoLog << '\n';
    }

    unsigned int fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n"
            << infoLog << '\n';
    }

    unsigned int shaderProgram{glCreateProgram()};
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_ERROR\n"
            << infoLog << '\n';
    }


    float verticies[]{
       -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
          0.0f, 0.5f,0.0f, // top
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1 ,&VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.6f,0.6f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        glfwSwapBuffers(window);
    }



    glfwTerminate();
    return 0;
}


void frameWindow_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
}

/*
 * TODO:
 *  Setup window    DONE.
 *  Setup Shaders   DONE.
 *  Setup Program   DONE.
 *  Setup VBO
 *  Setup VAO
 *  DRAW
 */
