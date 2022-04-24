#include "Rect.h"

#include <cmath>
#include "glad/glad.h"
#include "Circle.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


Rect::Rect(glm::vec2 _pos, glm::vec2 _size) : 
position(_pos),
size(_size),
translation(glm::mat4(1)),
color(0.266f, 0.478f, 0.792f,1.0f),
isColliding(false)
{
    rotation =glm::mat4(1);
    scale = glm::mat4(1);
    translation = glm::translate(translation, glm::vec3(position.x, position.y, 0));
    scale = glm::scale(scale, glm::vec3(size.x, size.y, 1.0));

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
   
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
   
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
Rect::~Rect()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}


void Rect::draw(const glm::mat4 &projection, const glm::mat4 &view)
{
    if (isColliding)
    {
        color = glm::vec4(0.388f, 0.933f, 0.658f, 1.0f);
    }else{
        color = glm::vec4(0.266f, 0.478f, 0.792f, 1.0f);
    }
    glUseProgram(shaderProgram);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "u_Color");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, color.r, color.g, color.b, color.a);

    int projectionLocation = glGetUniformLocation(shaderProgram, "u_Projection");
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    int viewLocation = glGetUniformLocation(shaderProgram, "u_View");
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 model = translation * rotation * scale;
    int modelLocation = glGetUniformLocation(shaderProgram, "u_Model");
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size()));
}