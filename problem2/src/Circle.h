#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <vector>
#include <glm/glm.hpp>


#include "Types.h"
#include "Rect.h"


class Circle
{
public:
    Circle(glm::vec2 _pos, float _radius);
    ~Circle();
    void draw(const glm::mat4 &projection, const glm::mat4 &view);

    glm::vec2 position;
    float radius;
    glm::mat4 transform;

    glm::vec4 color;

    bool isColliding;

    bool circleColision(Rect& _rectObj);

private:
    const char *vertexShaderSource = "#version 460 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "uniform mat4 u_Projection;\n"
                                     "uniform mat4 u_View;\n"
                                     "uniform mat4 u_Model;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = u_Projection*u_View*u_Model*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 460 core\n"
                                       "out vec4 FragColor;\n"
                                       "uniform vec4 u_Color;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = u_Color;\n"
                                       "}\n\0";

    std::vector<glm::vec2> vertices;
    uint VAO;
    uint VBO;
    uint shaderProgram;
};
#endif
