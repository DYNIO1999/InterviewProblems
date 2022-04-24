#include <cmath>
#include "glad/glad.h"
#include "Circle.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

inline static std::vector<glm::vec2> createCircleVertices(int _triangles){

    std::vector<glm::vec2> vertices;

    int numberOfVertcies = _triangles + 2;
    int circleIdx = 1;
    for (int i = 0; i < numberOfVertcies; i++)
    {
        float x = (cosf(circleIdx * 2.0 * M_PI / _triangles));
        float y = (sinf(circleIdx * 2.0 * M_PI / _triangles));
        vertices.push_back(glm::vec2(x,y));
        circleIdx++;
    }

    return vertices;
}

Circle::Circle(glm::vec2 _pos, float _radius):
position(_pos), 
radius(_radius),
transform(glm::mat4(1)),
color(0.266f, 0.478f, 0.792f,1.0f),
isColliding(false)
{

    transform = glm::translate(transform, glm::vec3(position.x, position.y,0));
    transform = glm::scale(transform, glm::vec3(radius, radius, 1.0));
    
    vertices = createCircleVertices(100);

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
Circle::~Circle(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

bool Circle::circleColision(Rect &_rectObj)
{
    float circleBasedOnRotaionX = (position.x - _rectObj.position.x) * cos(_rectObj.rotationAngle) - (position.y - _rectObj.position.y) * sin(_rectObj.rotationAngle);
    float circleBasedOnRotaionY = (position.x - _rectObj.position.x) * sin(_rectObj.rotationAngle) + (position.y - _rectObj.position.y) * cos(_rectObj.rotationAngle);

    float distanceX = std::max(std::abs(circleBasedOnRotaionX) - _rectObj.size.x, 0.0f);
    float distanceY = std::max(std::abs(circleBasedOnRotaionY) - _rectObj.size.y, 0.0f);

    float squaredDistance = distanceX * distanceX + distanceY * distanceY;

    return squaredDistance <=radius*radius;
}

void Circle::draw(const glm::mat4 &projection, const glm::mat4 &view)
{
    if(isColliding){
        color = glm::vec4(0.388f, 0.933f, 0.658f,1.0f);
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

    int modelLocation = glGetUniformLocation(shaderProgram, "u_Model");
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<int>(vertices.size()));
}