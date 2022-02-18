#include "Libs/glad/glad.h" // you can change this to your glad location just make sure that glad is included before glfw
#include <GLFW/glfw3.h>
#include <iostream>


const char* vertexShaderSource{ // creating the vertex shader
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "gl_Position = vec4(aPos.x,aPos.y, aPos.z, 1.0);\n"
    "}\0"
};


const char* fragmentShaderSource{ // creating the fragment shader
    "#version 460 core\n"
    "out vec4 FragColour;\n"
    "void main(){\n"
    "FragColour= vec4(0.3, 0.2,0.5,1.0);\n"
    "}\0"
};


void frameWindow_callback(GLFWwindow* window, int width, int height); // setting the viewport window callback so the
// viewport window changes when we resize the screen

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
    glfwMakeContextCurrent(window); // making the current context the window
    // do this before initialising glad otherwise errors will happen

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){// initialising glad
        std::cout << "COULD NOT LOAD GLAD\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,1200,880); // setting the base viewport size (same as window originally)
    glfwSetWindowSizeCallback(window, frameWindow_callback);// setting the window size callback using the frameWindow_callback  function pointer
    // basically changing the viewport size anytime we resize the window (like what i said earilier in the funcion decleration)


    int success;     // used for checking if the shader compiled successfully and other stuff
    char infoLog[512]; // used to store the error messages and output them

    unsigned int vertexShader{glCreateShader(GL_VERTEX_SHADER)}; // creating a shader, the function returns a shader id that attaches to the variable
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); // adding the shader source to the shader we created
    glCompileShader(vertexShader); // compiling the shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // checking if the shader compiled successfully and changing the status of the success var accordingly
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog); // if a failed compile we get the error message and store it in infoLog
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n"
            << infoLog << '\n'; // we write what part of the code failed and then the error message
    }

    unsigned int fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)}; // creating the fragmentShader same as vertex shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n"
            << infoLog << '\n';
    }

    unsigned int shaderProgram{glCreateProgram()}; // creating the shader program so we can easily manipulate the vertex and fragment shader
    glAttachShader(shaderProgram, vertexShader); // attaching the vertex shader to the program
    glAttachShader(shaderProgram, fragmentShader); // attaching the fragment shader to the shader program
    glLinkProgram(shaderProgram); // linking everything together
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // checking the linking status using the success
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_ERROR\n"
            << infoLog << '\n';
    }

    float verticies[]{ // creating the shape verticies
       -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
          0.0f, 0.5f,0.0f, // top
    };

    unsigned int VBO, VAO; // creating the vertex buffer object and array object
    glGenBuffers(1, &VBO); // attaching the id to the objects
    glGenVertexArrays(1 ,&VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding  the objects
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); //copies the vertex data into the vertex memory

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr); // telling opengl how it should interperate the vertex data
    glEnableVertexAttribArray(0);// enabling hte vertex attrib array with the location of the vertex

    glBindBuffer(GL_ARRAY_BUFFER, 0); // we can safley unbind these now
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.6f,0.6f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glUseProgram(shaderProgram); // these dont need to be inside the while loop
        glBindVertexArray(VAO); // these dont need to be inside the while loop
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
