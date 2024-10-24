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

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
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
    
    // ----------------- SHADER PROGRAM -----------------

    unsigned int shaderProgram1 = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    unsigned int shaderProgram2 = createShaderProgram(vertexShaderSource, fragmentShaderSource2);
    
    // ----------------- VERTEX DATA -----------------

    // Vertex data for first rectangle
    float firstRectangle[] = 
    {
        0.6f,  0.6f, 0.0f,  // Top right
        0.6f, -0.6f, 0.0f,  // Bottom right
       -0.1f, -0.6f, 0.0f,  // Bottom left
       -0.1f,  0.6f, 0.0f   // Top left 
    };

    // Vertex data for second rectangle
    float secondRectangle[] = 
    {
        0.1f,  0.4f, 0.0f,  // Top right
        0.1f, -0.4f, 0.0f,  // Bottom right
       -0.6f, -0.4f, 0.0f,  // Bottom left
       -0.6f,  0.4f, 0.0f   // Top left 
    };

    // Indices for two rectangles (each rectangle is made up of two triangles)
    unsigned int indices[] = 
    { 
        // First rectangle
        0, 1, 3,   // First triangle
        1, 2, 3,   // Second triangle
    };

    // ----------------- VERTEX BUFFER AND ATTRIBUTES -----------------
    
    unsigned int VBOs[2], VAOs[2], EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);

    // first rectangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstRectangle), firstRectangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second rectangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondRectangle), secondRectangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // unbind VAO to avoid accidental changes
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO to avoid accidental changes
    
    while(!glfwWindowShouldClose(window))
    {
        // ----------------- INPUT -----------------
        processInput(window);

        // ----------------- RENDERING -----------------
        glClearColor(0.5f, 0.2f, 0.2f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use shader program and rebind vertex array object (also binds VBO and vertex attributes)
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // uses currently bound VAO

        // render second triangle with different VAO/VBO & shader
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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