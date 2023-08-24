#pragma once
#include <GLAD/glad.h>
#include <iostream>

class VertexBuffer
{
public:
    VertexBuffer(int objID, float vertices[], int verticesSize)
    {
        //Initialising Vertex Buffer Object.
        unsigned int VBO;
        glGenBuffers(objID, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    }
    void finBindBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};