#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shaders/Shader.h>
#include <Texture.h>
#include <VertexBuffer.h>

#include <iostream>
#include <string>

GLFWwindow* window;

unsigned int VAO, EBO, texture1, texture2;

const unsigned int screenWidth = 1920, screenHeight = 1080;

/* Cube vertices */
float vertices[] = {
    -0.2f,  1.0f, -0.0f,  1.0f, 0.0f,
     0.2f,  1.0f, -0.0f,  0.0f, 0.0f,
     0.0f,  0.4f,  0.3f,  0.5f, 1.0f,

     0.0f,  0.0f,  0.3f,  1.0f, 0.0f,
     0.0f,  0.4f,  0.3f,  0.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

     0.0f,  0.0f,  0.3f,  1.0f, 0.0f,
     0.0f,  0.4f,  0.3f,  0.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -0.2f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.0f,  0.4f,  0.3f,  0.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

     0.2f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.0f,  0.4f,  0.3f,  0.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

     1.0f,  0.0f, -0.0f,  1.0f, 0.0f,
     1.0f,  0.3f,  0.0f,  0.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -1.0f,  0.3f, -0.0f,  0.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

     0.8f,  0.1f,  0.15f, 1.0f, 0.0f,
     1.0f,  0.3f,  0.0f,  0.0f, 0.0f,
     0.2f,  1.0f,  0.0f,  0.5f, 1.0f,

    -0.8f,  0.1f,  0.15f, 1.0f, 0.0f,
    -1.0f,  0.3f, -0.0f,  0.0f, 0.0f,
    -0.2f,  1.0f,  0.0f,  0.5f, 1.0f,

    -0.0f,  0.0f,  0.3f,  1.0f, 0.0f,
    -0.0f,  0.05f, 0.15f, 0.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -0.0f,  0.05f, 0.15f, 1.0f, 0.0f,
    -0.0f,  0.0f, -0.0f,  0.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -0.0f,  0.0f,  0.3f,  1.0f, 0.0f,
    -0.0f,  0.05f, 0.15f, 0.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -0.0f,  0.05f, 0.15f, 1.0f, 0.0f,
    -0.0f,  0.0f, -0.0f,  0.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -1.0f,  0.3f,  0.0f,  0.0f, 0.0f,
    -0.8f,  0.1f,  0.0f,  0.5f, 1.0f,

    -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.8f,  0.1f,  0.0f,  0.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

     1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     1.0f,  0.3f,  0.0f,  0.0f, 0.0f,
     0.8f,  0.1f,  0.0f,  0.5f, 1.0f,

     1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.8f,  0.1f,  0.0f,  0.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.5f, 1.0f,

    -0.8f,  0.1f,  0.0f,  1.0f, 0.0f,
    -1.0f,  0.3f,  0.0f,  0.0f, 0.0f,
    -0.2f,  1.0f, -0.0f,  0.5f, 1.0f,

     0.8f,  0.1f,  0.0f,  1.0f, 0.0f,
     1.0f,  0.3f,  0.0f,  0.0f, 0.0f,
     0.2f,  1.0f, -0.0f,  0.5f, 1.0f,

    -0.8f,  0.1f,  0.0f,  1.0f, 0.0f,
    -0.8f,  0.1f,  0.15f, 0.0f, 0.0f,
    -0.2f,  1.0f, -0.0f,  0.5f, 1.0f,

     0.8f,  0.1f,  0.0f,  1.0f, 0.0f,
     0.8f,  0.1f,  0.15f, 0.0f, 0.0f,
     0.2f,  1.0f, -0.0f,  0.5f, 1.0f,

     0.8f,  0.1f,  0.15f, 1.0f, 0.0f,
    -0.0f,  0.0f, -0.0f,  0.0f, 0.0f,
     0.2f,  1.0f, -0.0f,  0.5f, 1.0f,

    -0.8f,  0.1f,  0.15f, 1.0f, 0.0f,
    -0.0f,  0.0f, -0.0f,  0.0f, 0.0f,
    -0.2f,  1.0f, -0.0f,  0.5f, 1.0f,

    -0.0f,  0.0f, -0.0f,  1.0f, 0.0f,
    -0.2f,  1.0f, -0.0f,  0.0f, 0.0f,
     0.2f,  1.0f, -0.0f,  0.5f, 1.0f,
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

glm::mat4 model = glm::mat4(1.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        //cameraPos += cameraSpeed * cameraFront;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        //cameraPos -= cameraSpeed * cameraFront;
        model = glm::rotate(model, glm::radians(-90.0f)* deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime , glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime , glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        //cameraPos += cameraSpeed * cameraFront;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        //cameraPos -= cameraSpeed * cameraFront;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {
        //cameraPos += cameraSpeed * cameraFront;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        //cameraPos -= cameraSpeed * cameraFront;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(-90.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    {
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        model = glm::rotate(model, glm::radians(90.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    /*float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; 
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);*/
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "";
}

void debugModeStart(int wireFrameOn)
{
    if (wireFrameOn == 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

static int initialiseGLFWWindow(int screenWidth, int screenHeight) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Game_OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Initialising GLAD - must be done before calling OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

int WinMain(void)
{
    initialiseGLFWWindow(screenWidth, screenHeight); //Screen Width, Screen Height

    std::string vertexFile = "resources/shaders/Vertex_Shader.vs", fragmentFile = "resources/shaders/Fragment_Shader.fs";;

    glEnable(GL_DEPTH_TEST);

    Shader gameShader(vertexFile.c_str(), fragmentFile.c_str());

    glGenVertexArrays(1, &VAO);
    VertexBuffer vertexBufferObj(1, vertices, sizeof(vertices));
    glBindVertexArray(VAO);

    //Sets vertex attribute pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //Texture mapping
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vertexBufferObj.finBindBuffer();
    glBindVertexArray(0);

    //Setting texture filepath.
    std::string textureFile = "resources/textures/shiptexture2.jpg", textureFileTwo = "resources/textures/shiptexture.jpg";
    //Loading textures
    Texture texture1(textureFile.c_str(), false);
    Texture texture2(textureFileTwo.c_str(), false);

    gameShader.use();
    gameShader.setInt("texture1", 0);
    gameShader.setInt("texture2", 1);

    debugModeStart(0); //Wireframe

    //Setting model starting location.
    model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //Takes button input every frame.
        processInput(window);

        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        texture1.applyTexture();
        glActiveTexture(GL_TEXTURE1);
        texture2.applyTexture();

        //Activating shader program.
        gameShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

        gameShader.setMat4("projection", projection);
        gameShader.setMat4("view", view);

        glBindVertexArray(VAO);

        model = glm::translate(model, glm::vec3(0.0f, -0.0f, 0.0f));

        gameShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 72);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}