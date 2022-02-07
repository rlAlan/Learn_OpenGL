#include "Libs/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

void fallback_sizescreen(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource{
  "#version 460 core\n"
  "layout (location = 0) in vec3  aPos;\n"
  "void main(){\n"
  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0"
};

const char* fragmentShaderSource{
  "#version 460 core\n"
  "out vec4 FragColour;\n"
  "void main(){\n"
  "FragColour = vec4(0.3f, 0.5f, 0.5f,1.0f);\n"
  "}\0"
};


int main()
{
  if(!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window{glfwCreateWindow(1000, 880, "Welcome", nullptr, nullptr)};
  if(window == nullptr){
    std::cout << "Failed to create window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Glad could not be loaded\n";
    glfwTerminate();
    return -1;
  }
  glViewport(0,0,1000,880);
  glfwSetWindowSizeCallback(window,fallback_sizescreen);

  float verticies[]{
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), vertexShaderSource, GL_STATIC_DRAW);

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource,nullptr);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n"
      << infoLog << '\n';
  }
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource,nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader,512, nullptr,infoLog);
    std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n"
      << infoLog << '\n';
  }

  unsigned int shaderProgram{glCreateProgram()};
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(shaderProgram, 512,nullptr, infoLog);
    std::cout << "SHADER_PROGRAM::LINK_FAILED\n"
      << infoLog << '\n';
  }

  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glUseProgram(shaderProgram); // activate the newly created shader Program



  while(!glfwWindowShouldClose(window)){
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    processInput(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}

void fallback_sizescreen(GLFWwindow* window, int width, int height){
  glViewport(0,0,width,height);
}

