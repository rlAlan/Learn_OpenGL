# Hello Triangle in OpenGL

In OpenGl everything is in 3d space unless explicitly stated otherwise.
All shapes have x, y,z axis.

The issue is that although opengl is in 3d  the screens pixles are 2D so a large
part of opengl is transforming these 2d pixels into somethign that looks 3d and vice
versa. This is what the graphcis pipeline does.

The hraphics pipeline takes input as a set of 3d coordinates and transforms them 
to colourd 2d pixels on the screen. It has a multitude of steps where hte output
of the last is input for the next.

Because of their parallel nature, graphics cards now have tiny little cores
that run small programs on teh GPU for each step of the graphics pipeline
these small programs are called shaders

### Graphics pipeline
Vertex Data[] -> Vertex shader[configurable] -> shape assembly -> geometry shader [configurable]
-> Rasterisation -> fragment shader[configurable] -> tests and blending

In order for Opengl to know what to make of you collection of coordinates
and color values OpenGL requires us to hint to what kind of render type we want
to form with the data. We can do this through the use of primitive types
GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP

The main purpose of the vertex shader is to transforms 3d coordinated into
different 3d coords

the shape assembly takes in all verticies (or vertex) from the vertex shader
and assembles all hte points together

the geometry shader then takes in output of the shape assembly and generates
other shapes by emitting new verticies to form new or other primitvs

the rasteriser then takes in the shapes where they are mapped to corresponding
pixels on the final screen resulting in fragments for the fragment shader
 clipping is when opengl discards all fragments not in the viewport
 (A fragment is all opengl needs to render a single pixel)


### Vertex input
To draw something we need to give openGl vertex data (in 3d just set all z to 0)
since we want to render a triangle we need to specify three verticies

float verticies[]{
 -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f,  0.0f,
};
these verticies will then be placed in a small space called the normalized device coordinates (NDC)
which has x, y and z ranging from -1 to 0 the NDC will then be transfered into screen coordinates 
using the data provided by the glViewport

## Simple

Opengl is 3D based so everything is in 3D unless stated otherwise

To convert from 3D to the pixels on the screen and vice versa we have the graphics
pipeline:
Vertex Data[] -> Vertex shader[configurable] -> shape assembly -> geometry shader [configurable]
-> Rasterisation -> fragment shader[configurable] -> tests and blending

Vertex data[] is the position of the verticies for the shape we want. This is passed to the
vertex shader, but before we do that we need to hint at openGl how we want it to organise the verticies
this is done using **primitives** like GL_TRIANGLES, GL_LINE_STRIP, GL_POINTS

float verticies[]{ // vertex data
 -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f,  0.0f,
};

The Vertex data[] is sent to a small place called the normalized device coordinates (NDC)
where it is plotted -1, 1 the NDC is then translated into screen space coordinates through the 
information passed in through glViewport 

The vertex data[] is then passed into teh vertex shader but is first temporarily stored
in the gpu's memoery which is then directly processed by the vertex shader.

we manage this memory through Vertex buffer objects (VBO)
because of this we can send in large amounts of data at once without having to send data
one vertex at a time

A VBO is a first occurance of opengl object and just like other opengl objects this buffer has a 
unique ID corresponding to that buffer, so we can generate one with a buffer id using 
the glGenBuffers function : unsigned int VBO; glGenBuffers(1, &VBO);

openGL has many buffer type and buffer type of a vertex buffer object is GL_ARRAY_BUFFER.
we can bind several bufferes at onve as long s they have a different type
using the glBindBuffer(GL_ARRAY_BUFFER, VBO);

from that point on any calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently
bound buffer, VBO. 

glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW)
thus is a function that specifically targets userdefined data into currently bound buffer
(first argumnat is type of buffer, size in bytes we want to pass, actual data we want to send, how we want the graphics
card to manage given data) the lsat can take multiple forms:
GL_STREAM_DRAW   The Data is set only once and used by the GPU
GL_STATIC_DRAW   The Data is set only onve and is used many times
GL_DYNAMIC_DRAW  The Data is changed a lot and used many times

### Shaders
in GLSL we declare the version and the profile 330 = 3.3 etc
so #version 460 core (version 4.6 using core profile)
layout (location = 0) in vec3 aPos; 
make a var of vec3 called aPos 

void main()
{
gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0f); 
will be used as the output of the vertex shader
}

to compile a shader we can store it as a const C string at the top of the file

for opengl to use the shader it needs to dynamically compile it at run-time from the source code
to do this we first need to create a shader object (again wiht its unique ID)
unisigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER) then attach shader source code
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL) then compile
glCompileShader(vertexShader)

we can then check if the shaders worked properly

complete code for making a shader:
```
// making the shader
  int success;
  char infoLog[512];
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
// cheking if it works
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success); 
  if(!success){
    glGetShaderInfoLog(vertexShader, 512,NULL,infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
  }
```

Fragment shader is another shader we need to make a triangle 
it is in charge of calculating colour ouput of pixels, 
graphics are represented as RGBA from 0.0 to 1.0

```CPP

const char* fragmentShaderSource{
  "#version 460 core\n"
  "out vec4 FragColour;\n"
  "void main(){\n"
  "FragColour = vec4(0.2, 0.6, 0.6, 1.0);\n"
  "}\n"
};


unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource,NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n"
      << infoLog << '\n';
  }

```

now that we have gotten the shaders ready for drawing a traingle we need to link it all
together we can do this through a program called a shader program which links multiple
shaders together and then we activate this program when rendering objects

since the output of one becomes the input of another we will get most of the errors here if they
do not match

```
unsigned int shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

```

the vertex shader allows us to specify any input we want in the form of vertex attributes
this mean swe need to manually specify what part of out inut data goes to which vertex attribute

our vertex buffer data is formatted as a section of memory 
where each vertex takes 12bytes (3 * 4bytes since they are floats)
x: 4byets, y: 4bytes, z: 4bytes all in a row for all 3 verticies

```
glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
the first argument specifies which vertex attribute we want to configure. We set the position of the
vertex attribute in the shader (location = 0) and since we want to pass data
to this vertex attribute, we pass in 0;

the next argument specifies the size of the vertex attribute which is a vec3 
so it is made of 3 values

the third argument specifies the type of the data which is GL_FLOAT(a vec* in GLSL is a float)

the next argument specifies if we want the data to be normalized, if were inputting
integer data types we would set this to GL_TRUE, the int data is normalized to 0 (or -1 for
signed data) and 1 when converted to float

the fifth argument is the stride and just says hwo much space between consecutive vertex attribs
(the size of 3 float since we have x,y,z for a vertex)

the final argument is of  type void* and needs the cast, this is to offset where the position
data begins in teh buffer 
```

----------------------
Each vertex attribute takes its data from memory managed by a VBO and which VBO it
takes its data from (you can have multiple VBOs) is determined by the VBO currently
bound to GL_ARRAY_BUFFER when calling glVertexAttribPointer. Since
the previously defined VBO is still bound before calling glVertexAttribPointer
vertex attribute 0 is now associated with its vertex data.
----------------------

Drawing an object in opengl would now look something like this:

// 0. copy verticies array in buffer for openGL
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

// 1. set the vertex attribute pointers
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,3*sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// 2. use shader program whenr we want to render an object)
glUseProgram(shaderProgram);

// 3. draw the object
usingSomeopenglFunc();

When we want to draw multiple different objects and stuff we would need to go through this
every single time which is cumbersome so we have something called a VAO
(Vertex array object) can be bound like a VBO and any subsequent vertex attrib calls from that point on will 
be stored inside the VAO. This means that when we want to configure attribute
pointers 

----------------------------------------------------------------------------
# Simpler 
We have verticies, We need to pump the verticies into the GPU, 
First we hold the verticies in the GPU memory to manage this memory
we have the VBO (Vertex Buffer Object) that store a large number of verticies 
once the Verticies are in GPU memory the vertex shader can access it quick

VBO is an opengl object so we need to generate its own ID
we then Bind the buffer to the object and give it a GL_ARRAY_BUFFER target 
so any call on GL_ARRAY_BUFFER be used to configure the bound buffer

Then we call the glBufferData function that copied the defined vertex data into
the buffers memory

{brief look into shaders: look at the above work cba to explain};
vertex shader allows us to specify any input we want in the form of vertex
attributes. This means we need to specify what part of our own input data
goes to which vertex attribute in the vertex shader. Meaning we need to specify
how opengl handles the vertex data before rendering.

the vertex buffer is as follows 

- the position is stored as 32bit (4byte) floating point values
- Each point is composed of 3 of those values
- No space between each set of data
- the first value is the begining
 with this knowledge we can tell OpenGL how it should interpret the vertex data (per vertex attribute)
 using the glVertexAttribPointer function 
