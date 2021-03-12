#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>

#include <ctime>
#include <chrono>
#include <thread>

#include "Shader.h"
#include "Window.h"
#include "Mesh.h"

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

bool direction = true;
bool direction2 = true;
float triOffset = -2.0f;
float triIncrement = 0.5f;
float triMaxOffset = -0.4f;
float triOffset2 = -4.0f;
float triMaxOffset2 = -0.03f;

//Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateTriangle()
{
    unsigned int rectIndices[] =
    {
        0, 2, 1,
        0, 3, 2,
    };
    GLfloat rectVertices[] =
    {
        -1.0f, -1.0f, 0.0f, //0
        -1.0f, 1.0f, 0.0f,  //1
        1.0f, 1.0f, 0.0f,   //2
        1.0f, -1.0f, 0.0f,  //3
    };
    Mesh* rect = new Mesh();
    rect->CreateMesh(rectVertices, rectIndices, 12, 6);
    meshList.push_back(rect);

    GLfloat triangleVertices[] =
    {
        -1.0f, -1.0f, 0.0f, //0
        1.0f, -1.0f, 0.0f,  //1
        0.0f, 1.0f, 0.0f,   //2
    };
    unsigned int triangleIndices[] =
    {
        0, 1, 2,
    };
    Mesh* triangle = new Mesh();
    triangle ->CreateMesh(triangleVertices, triangleIndices, 9, 3);
    meshList.push_back(triangle);

     GLfloat circlevertices[] =
    {
        0.0f, 0.0f, 0.0f,       //0
        1.0f, 0.0f, 0.0f,       //1
        0.98f, 0.18f, 0.0f,     //2
        0.93f, 0.35f, 0.0f,     //3
        0.82f, 0.56f, 0.0f,     //4
        0.70f, 0.71f, 0.0f,     //5
        0.56f, 0.82f, 0.0f,     //6
        0.35f, 0.93f, 0.0f,     //7
        0.18f, 0.98f, 0.0f,     //8
        0.0f, 1.0f, 0.0f        //9

    };

    unsigned int circleindices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9

    };

    Mesh* circle = new Mesh();
    circle->CreateMesh(circlevertices, circleindices, 30, 24);
    meshList.push_back(circle);

}

void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

void Update(long elapsedTime)
{
    if (direction)
    {
        //s += v * dt
        triOffset += (triIncrement * elapsedTime / 1000.0);
    }
    else
    {
        triOffset -= (triIncrement * elapsedTime / 1000.0);
    }
     
    if (direction && triOffset >= triMaxOffset) direction = false;
    if (!direction && triOffset <= -triMaxOffset) direction = true;

    if (direction2)
    {
        //s += v * dt
        triOffset2 += (triIncrement * elapsedTime / 1000.0);
    }
    else
    {
        triOffset2 -= (triIncrement * elapsedTime / 1000.0);
    }
     
    if (direction2 && triOffset2 >= triMaxOffset2) direction2 = false;
    if (!direction2 && triOffset2 <= -triMaxOffset2) direction2 = true;

}

int main()
{
    //current animation time
    auto currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    //last frame animation time
    long lastTime = currentTime;
    //elapsed time
    long elapsedTime;

    mainWindow = Window(WIDTH, HEIGHT);
    mainWindow.initialise();

    CreateTriangle();
    CreateShaders();

    GLuint uniformModel = 0, uniformProjection = 0, uniformColor = 0;
    glm::vec4 color;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    //Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        elapsedTime = currentTime - lastTime;

        lastTime = currentTime;

        //Get + Handle user input events
        glfwPollEvents();
        
        Update(elapsedTime);
        
        //Clear window
        glClearColor(1.0f, 0.87843137f, 0.50980392f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw here

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformColor = shaderList[0].GetColorLocation();

        /*  */
        glm::mat4 model(1.0f);

        //Model 2: Wipping Cream
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.45f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//2
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.15f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//4
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.05f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//5
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.05f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//6
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//7
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//8
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//9
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//10
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//11
         model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.45f, -triOffset2-0.35f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(255.0, 255.0, 255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//12

        //Model 1: Pancake Base

        //Component 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset, -1.5f));
        model = glm::scale(model, glm::vec3(0.6f, 0.2f, 1.0f));
        color = glm::vec4(173.0/255.0, 84.0/255.0, 0.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }

        //Component 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset - 0.05f, -1.5f));
        model = glm::scale(model, glm::vec3(0.6f, 0.07f, 1.0f));
        color = glm::vec4(228.0/255.0, 172.0/255.0, 121.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        //Component 3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset - 0.1f  , -1.5f));
        model = glm::scale(model, glm::vec3(0.6f, 0.2f, 1.0f));
        color = glm::vec4(228.0/255.0, 172.0/255.0, 121.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }

 

        glUseProgram(0);

        //end draw

        mainWindow.swapBuffers();
    }

    return 0;
}