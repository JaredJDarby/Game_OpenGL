#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <Shaders/Shader.h>

#include <iostream>

GLFWwindow* window;

//Setting up Vertex Buffer Object, Vertex Array Object and Element Buffer Object
unsigned int VBO, VAO, EBO;

/* Triangle vertices */
float vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//bottom right
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom left
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f//top left
};
unsigned int indicies[] = {
    0, 1, 3,
    1, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void debugMode(int wireFrameOn)
{
    if (wireFrameOn == 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void initialiseShaderObjects()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    //Copies array of verties into a buffer for use.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    //Sets vertex attribute pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

    //Initialising GLAD - must be done before calling OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
}

int main(void)
{
    initialiseGLFWWindow(1920, 1080); //Screen Width, Screen Height

    Shader gameShader("D:/Documents/Programming/C++/Game_OpenGL/src/Shaders/Vertex_Shader.vs", "D:/Documents/Programming/C++/Game_OpenGL/src/Shaders/Fragment_Shader.fs");

    initialiseShaderObjects();

    debugMode(0); //Wireframe

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Takes button input every frame.
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Activating shader program.
        gameShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}