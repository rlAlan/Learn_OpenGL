#include "Libs/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>


void fallback_screenView(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource{
  "#version 460 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main(){\n"
  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0"
};

const char* fragmentShaderSource{
  "#version 460 core\n"
  "out vec4 FragColor;\n"
  "void main(){\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0"
};

int main()
{
  if(!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window{glfwCreateWindow(1000, 880, "Window", NULL, NULL)};
  if(window == NULL){
    std::cout << "GLFW failed to create window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "GLAD failed to initialise\n";
    return -1;
  }

  glViewport(0,0,1000, 880);
  glfwSetWindowSizeCallback(window, fallback_screenView);

  float verticies[]{
    -0.5f, -0.5f, 0.0f,
    0.5f,  -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
  };
  unsigned int VDO;
  glGenBuffers(1, &VDO);
  glBindBuffer(GL_VERTEX_ARRAY, VDO);
  glBufferData(GL_VERTEX_ARRAY, sizeof(verticies), &verticies,GL_STATIC_DRAW);

  int success;
  char infoLog[512];
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
  if(!success){
    glGetShaderInfoLog(vertexShader, 512,NULL,infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader, 512,NULL,infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
  }



  while(!glfwWindowShouldClose(window))
  {
    glClearColor(0.2f, 0.6f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glfwTerminate();
  return 0;
}


void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}


void fallback_screenView(GLFWwindow* window, int width, int height){
  glViewport(0,0,width,height);
}
