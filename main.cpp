#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";



int main()
{
    // ----------------- GLFW -----------------
    // initialise and configure glfw
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // create a window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    std::cout << "Creating GLFW window" << std::endl;
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ----------------- GLAD -----------------

    // initialise GLAD (load OpenGL function pointers)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    
    // ----------------- VERTEX SHADER -----------------
    // creating vertex shader and compiling it with source code
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // error checking in vertex shader
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error: Vertex shader compilation failed" << infoLog << std::endl;
    }

    std::cout << "Vertex shader compiled" << std::endl;

    // ----------------- FRAGMENT SHADER -----------------

    // creating fragment shader and compiling it with source code
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // error checking in fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error: Fragment shader compilation failed" << infoLog << std::endl;
    }

    std::cout << "Fragment shader compiled" << std::endl;

    // ----------------- SHADER PROGRAM -----------------

    // create shader program to render them
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // link shaders to shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // error checking in shader program
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error: Shader program linking failed" << infoLog << std::endl;
    }

    std::cout << "Shader program linked" << std::endl;

    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ----------------- VERTEX DATA -----------------

    float vertices[] = 
    {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };

    // order in which they are drawn
    unsigned int indices[] = 
    { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };
    // ----------------- VERTEX BUFFER AND ATTRIBUTES -----------------

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // bind the Vertex Array Object first as it holds state of the VBO, EBO and vertex attributes
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    // copy vertices and indices data into VBO and EBO buffers respectively
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // layout (location = 0) so modify vertex attribute 0
        // 3 floats per vertex (vec3)
        // float data type
        // not normalized
        // stride is 3 floats
        // the offset of the buffer is 0 (start at beginning)
    glEnableVertexAttribArray(0);
        // enable the vertex attribute at 0 (location = 0)


    // unbind VBO and VAO to avoid accidental changes, OpenGL has saved the state once the VAO was bound
    // EBO is not saved so cannot be unbound
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while(!glfwWindowShouldClose(window))
    {
        // ----------------- INPUT -----------------
        processInput(window);

        // ----------------- RENDERING -----------------
        glClearColor(0.5f, 0.2f, 0.2f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use shader program and rebind vertex array object (also binds VBO and vertex attributes)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // draw triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // uses currently bound VAO
        
        // unbind VAO to avoid accidental changes
        glBindVertexArray(0); 

        // ----------------- SWAP BUFFERS AND POLL EVENTS -----------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
        
    return 0;
}

// methods
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // escape to exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }
    
}
