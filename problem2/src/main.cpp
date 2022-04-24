#include <cassert>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Circle.h"
#include "Rect.h"


/*
Napisz wizualizator kolizji koła (statycznie położonego na środku ekranu) i obracającego się
prostokąta (obrót poprzez naciśnięcie odpowiednich klawiszy np. q, e albo strzałki). Kolizja
powinna być zasygnalizowana np. poprzez komunikat lub zmianę koloru obiektów.
*/


static GLFWwindow* window;
static glm::mat4 projection = glm::mat4(1);
static glm::mat4 view = glm::mat4(1);

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void initWindow(){
    glfwInit();
    window = glfwCreateWindow(1600, 900, "Problem2", NULL, NULL);
    assert(window != nullptr && "Failed to create GLFW window");
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    int checkError = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(checkError != 0 && "Failed to initialize GLAD");
}
void shutDown(){
    glfwDestroyWindow(window);
}


int main(int argc, char const *argv[])
{
    initWindow();

    float lastFrameTime;
    float deltaTime;

    Circle circle(glm::vec2(800,450), 200);
    Rect rect(glm::vec2(490,450),glm::vec2(100,100));

    projection = glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, 1), 
        glm::vec3(0, 0, 0), 
        glm::vec3(0, 1, 0)  
    );

    glm::mat4 rotation(1);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            rect.rotation = glm::rotate(rect.rotation, 1.0f*deltaTime, glm::vec3(0.0f, 0.0f, -1.0f));
            rect.rotationAngle+= 1*deltaTime*(-1);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            rect.rotation = glm::rotate(rect.rotation, 1.0f*deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rect.rotationAngle += 1 * deltaTime * (1);
        }

        bool checkColision = circle.circleColision(rect);
        if(checkColision){
            circle.isColliding=true;
            rect.isColliding = true;
        }else{
            circle.isColliding = false;
            rect.isColliding = false;
        }
        
        circle.draw(projection, view);
        rect.draw(projection,view);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shutDown();

    return 0;
}
