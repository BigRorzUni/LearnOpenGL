#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; // position has attribute position 0\n"
"layout (location = 1) in vec3 aColour; // color has attribute position 1\n"
"out vec3 ourColour;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos, 1.0);\n"
" ourColour = aColour;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColour;\n"
"in vec3 ourColour;\n"
"void main()\n"
"{\n"
"FragColour = vec4(ourColour, 1.0);\n"
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
    
    // ----------------- SHADER PROGRAM -----------------

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    
    // ----------------- VERTEX DATA -----------------

    float vertices[] = 
    {
    // positions        // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f // top
    };

    unsigned int indices[] = 
    { 
        0, 1, 2
    };

    // ----------------- VERTEX BUFFER AND ATTRIBUTES -----------------
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Triangle setup
    // --------------------
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind VBO and VAO to prevent accidental changes (not unbinding EBO because it is bound to VAO)
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    while(!glfwWindowShouldClose(window))
    {
        // ----------------- INPUT -----------------
        processInput(window);

        // ----------------- RENDERING -----------------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use shader program and rebind vertex array object (also binds VBO and vertex attributes)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // uses currently bound VAO

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

    // get current polygon mode
    GLint polygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygonMode);

    static bool tabPressedLastFrame = false;
    bool tabPressed = glfwGetKey(window, GLFW_KEY_TAB);

    // tab to switch between fill and line mode
    if(tabPressed && !tabPressedLastFrame)
    {
        if(polygonMode[0] == GL_LINE && polygonMode[1] == GL_LINE)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    tabPressedLastFrame = tabPressed;
}

unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    // ------- INIT ERROR CHECKING VARIABLES -------
    int success;
    char infoLog[512];

    // ----------------- VERTEX SHADER -----------------
    // creating vertex shader and compiling it with source code
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // error checking in vertex shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error: Vertex shader compilation failed" << infoLog << std::endl;
    }

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

    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}