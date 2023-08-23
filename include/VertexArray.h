#pragma once
#include <GLAD/glad.h>
#include <iostream>

class VertexArray
{
public:
    unsigned int VAO;
    VertexArray(int test)
    {

        //glGenVertexArrays(1, &VAO);
        //glBindVertexArray(VAO);

        //Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);
    }
    void finBindArray()
    {
        glBindVertexArray(VAO);
    }
    void drawArray()
    {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};