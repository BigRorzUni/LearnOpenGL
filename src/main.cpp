#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>
#include <model.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void escInput(GLFWwindow* window);
void tabInput(GLFWwindow* window);
void cameraInput(GLFWwindow* window);

unsigned int loadTexture(char const * path);
unsigned int loadCubemap(vector<std::string> faces);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f, lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    #pragma region GLFW & GLAD Initialisation
    // ----------------- GLFW INIT -----------------
    // initialise and configure glfw
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // create a window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // make the window the current context
    glfwMakeContextCurrent(window);

    // set the callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // locks cursor to window and hides it
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ----------------- GLAD -----------------
    // initialise GLAD (load OpenGL function pointers)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    
    #pragma endregion

    // set up vertex data 
    // -------------------------
    float cubeVertices[] = 
    {
    // positions          // texture coordinates
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
    };

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    // load textures
    // -------------
    int frontFacingTex = loadTexture("assets/container.jpg");
    int backFacingTex = loadTexture("assets/debug.png");

    // shader configuration
    // --------------------
    // build and compile shaders
    // -------------------------
    Shader redShader("shader.vs", "shader.fs");
    Shader blueShader("shader.vs", "shader.fs");
    Shader greenShader("shader.vs", "shader.fs");
    Shader yellowShader("shader.vs", "shader.fs");

    // setting the binding point for uniform buffer block
    unsigned int redIndex = glGetUniformBlockIndex(redShader.ID, "Matrices");
    unsigned int blueIndex = glGetUniformBlockIndex(blueShader.ID, "Matrices");
    unsigned int greenIndex = glGetUniformBlockIndex(greenShader.ID, "Matrices");
    unsigned int yellowIndex = glGetUniformBlockIndex(yellowShader.ID, "Matrices");

    glUniformBlockBinding(redShader.ID, redIndex, 0);
    glUniformBlockBinding(blueShader.ID, blueIndex, 0);
    glUniformBlockBinding(greenShader.ID, greenIndex, 0);
    glUniformBlockBinding(yellowShader.ID, yellowIndex, 0);

    // setting uniform buffer block
    unsigned int matricesBlock;
    glGenBuffers(1, &matricesBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, matricesBlock);
    glBufferData(GL_UNIFORM_BUFFER, 128, NULL, GL_STATIC_DRAW); // 128 bytes
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // bind uniform buffer object to that index as well
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, matricesBlock);
    // glBindBufferRange(GL_UNIFORM_BUFFER, 0, matricesBlock, 0, 128); // specify an offset so multiple ubos can be bound to one index


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        escInput(window);
        tabInput(window);
        cameraInput(window);

        // reset from last frame
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);   
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // transformation matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glBindBuffer(GL_UNIFORM_BUFFER, matricesBlock);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, &projection);
        glBufferSubData(GL_UNIFORM_BUFFER, 64, 64, &view);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glm::vec3 redColour(1.0f, 0.0f, 0.0f);
        glm::vec3 blueColour(0.0f, 0.0f, 1.0f);
        glm::vec3 greenColour(0.0f, 1.0f, 0.0f);
        glm::vec3 yellowColour(1.0f, 1.0f, 0.0f);

        // draw objects
        // ------

        glBindVertexArray(cubeVAO);

        // red cube
        redShader.use();
        redShader.setVec3("colour", redColour);
        model = glm::translate(model, glm::vec3(1.0f, -1.0f, -1.0f));
        redShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // blue cube
        blueShader.use();
        blueShader.setVec3("colour", blueColour);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 1.0f, -1.0f));
        blueShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // green cube
        greenShader.use();
        greenShader.setVec3("colour", greenColour);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 1.0f, -1.0f));
        greenShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // yellow cube
        yellowShader.use();
        yellowShader.setVec3("colour", yellowColour);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f));
        blueShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);




        // ----------------- SWAP BUFFERS AND POLL EVENTS --------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    glfwTerminate();
    return 0;
}

// ----------------- PROCESS INPUT -----------------
void escInput(GLFWwindow* window)
{
    // escape to exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
}

void tabInput(GLFWwindow* window)
{
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

void cameraInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        // check for the correct format of colour channels
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // RGBA needs to be clamped to prevent wrapping but do not clamp RGB
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

        // linear filtering for magnification and minification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

