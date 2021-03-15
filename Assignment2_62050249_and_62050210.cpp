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

//Model 1: Base Pancake Variable Init
bool direction = true;
float triOffset = -2.0f;
float triMaxOffset = -0.4f;

//Model 2: Wipping Cream Variable Init
bool direction2 = true;
float triOffset2 = -4.0f;
float triMaxOffset2 = -0.03f;

//Model 3: Top Pancake Variable Init
bool direction3 = true;
float triOffset3 = -6.0f;
float triMaxOffset3 = -0.25f;

//Model 4: Topping Variable Init
bool direction4 = true;
float triOffset4 = -8.0;
float triMaxOffset4 = -0.25f;

bool direction5 = true;
float triOffset5 = -10.0;
float triMaxOffset5 = 0.7f;

float triIncrement = 0.5f;


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
    //Model 1: Pancake Base Animation Direction
    if (direction) triOffset += (triIncrement * elapsedTime / 1000.0);

    if (direction && triOffset >= triMaxOffset) direction = false;
    if (!direction && triOffset <= -triMaxOffset) direction = true;
    
    //Model 2: Wipping Cream  Animation Direction
    if (direction2) triOffset2 += (triIncrement * elapsedTime / 1000.0);
     
    if (direction2 && triOffset2 >= triMaxOffset2) direction2 = false;
    if (!direction2 && triOffset2 <= -triMaxOffset2) direction2 = true;
    
    //Model 3: Top Pancake Animation Direction
    if (direction3) triOffset3 += (triIncrement * elapsedTime / 1000.0);
     
    if (direction3 && triOffset3 >= triMaxOffset3) direction3 = false;
    if (!direction3 && triOffset3 <= -triMaxOffset3) direction3 = true;
    
    //Model 4: Topping Animation Direction
    if (direction4) triOffset4 += (triIncrement * elapsedTime / 1000.0);
     
    if (direction4 && triOffset4 >= triMaxOffset4) direction4 = false;
    if (!direction4 && triOffset4 <= -triMaxOffset4) direction4 = true;

    //Model 5: Honey
    if (direction5) triOffset5 += (triIncrement * elapsedTime / 1000.0);
     
    if (direction5 && triOffset5 >= triMaxOffset5) direction5 = false;
    if (!direction5 && triOffset5 <= -triMaxOffset5) direction5 = true;

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

        glm::mat4 model(1.0f);

        /* Model 4: Topping */

        //cherry on top
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset4 -0.1f, -1.5f));
        model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(0.005f, 0.02f, 1.0f));
        model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(19.0/255.0, 74.0/255.0, 21.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset4 +0.15f, -1.5f));
        model = glm::scale(model, glm::vec3(0.045f, 0.045f, 1.0f));
        color = glm::vec4(210.0/255.0, 5.0/255.0, 45.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }

        //ice cream
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset4 , -1.5f));
        model = glm::scale(model, glm::vec3(0.23f, 0.03f, 1.0f));
        color = glm::vec4(255.0/255.0, 192.0/255.0, 193.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset4 + 0.08f, -1.5f));
        model = glm::scale(model, glm::vec3(0.2f, 0.1f, 1.0f));
        color = glm::vec4(255.0/255.0, 192.0/255.0, 193.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        
        /* Model 3: Top Pancake */

        //Component 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset3, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.0f, -triOffset3 - 0.05f, -1.5f));
        model = glm::scale(model, glm::vec3(0.6f, 0.07f, 1.0f));
        color = glm::vec4(228.0/255.0, 172.0/255.0, 121.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        //Component 3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset3 - 0.1f  , -1.5f));
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
        

        /* Model 2: Wipping Cream and banana and blueberry  */

        //banana
        //1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.04f, -triOffset2 -0.32f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.02f, -triOffset2 -0.32f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.02f, -triOffset2 -0.36f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 105 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.04f, -triOffset2 -0.36f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset2 -0.34f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(251.0/255.0, 242.0/255.0, 219.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -triOffset2 -0.36f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(253.0/255.0, 236.0/255.0, 190.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        //2 
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2 -0.34f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.42f, -triOffset2 -0.34f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.42f, -triOffset2 -0.38f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 105 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

         model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2 -0.38f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.4f, -triOffset2 -0.36f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(251.0/255.0, 242.0/255.0, 219.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.4f, -triOffset2 -0.38f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(253.0/255.0, 236.0/255.0, 190.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        //3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2 -0.34f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.42f, -triOffset2 -0.34f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.42f, -triOffset2 -0.38f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 105 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

         model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2 -0.38f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.01f, 1.0f));
        model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(190.0/255.0, 137.0/255.0, 5.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.4f, -triOffset2 -0.36f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(251.0/255.0, 242.0/255.0, 219.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.4f, -triOffset2 -0.38f, -1.5f));
        model = glm::scale(model, glm::vec3(0.09f, 0.09f, 1.0f));
        color = glm::vec4(253.0/255.0, 236.0/255.0, 190.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }
        //blueberry
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2 -0.25f, -1.5f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 1.0f));
        color = glm::vec4(70.0/255.0, 65.0/255.0, 150.0/255.0, 1);
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
        model = glm::translate(model, glm::vec3(-0.20f, -triOffset2 -0.25f, -1.5f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 1.0f));
        color = glm::vec4(70.0/255.0, 65.0/255.0, 150.0/255.0, 1);
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
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2 -0.45f, -1.5f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 1.0f));
        color = glm::vec4(70.0/255.0, 65.0/255.0, 150.0/255.0, 1);
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
        model = glm::translate(model, glm::vec3(0.2f, -triOffset2 -0.4f, -1.5f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 1.0f));
        color = glm::vec4(70.0/255.0, 65.0/255.0, 150.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }//2


        //Wipping Cream
        //Model 2 Row -1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.45f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.15f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.05f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.05f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2-0.25f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.45f, -triOffset2-0.25f, -1.5f));
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
        
        //Model 2 Row 0
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.50f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.15f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.05f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.05f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2-0.30f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.50f, -triOffset2-0.30f, -1.5f));
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
        
        //Model 2 Row 1
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
        
        //Model 2: Wipping Cream Row 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.52f, -triOffset2-0.40f, -1.5f));
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
        }//0
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.45f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.15f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.05f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.05f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2-0.40f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.45f, -triOffset2-0.40f, -1.5f));
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
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.52f, -triOffset2-0.40f, -1.5f));
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
        }//13
        
        //Model 2: Wipping Cream Row 3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.45f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.15f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.05f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.05f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2-0.45f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.45f, -triOffset2-0.45f, -1.5f));
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
        
        //Model 2: Wipping Cream Row 4
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.35f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.25f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.15f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(-0.05f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.05f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.15f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.25f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.35f, -triOffset2-0.50f, -1.5f));
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
        model = glm::translate(model, glm::vec3(0.45f, -triOffset2-0.50f, -1.5f));
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

        

        /*Model 1: Pancake Base */

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

        /* Model 5: Honey */  

        //H
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset5 +0.03f, 0.3f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.05f, 1.0f));
        color = glm::vec4(139.0/255.0, 102.0/255.0, 71.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset5, 0.3f, -1.5f));
        model = glm::scale(model, glm::vec3(0.04f, 0.008f, 1.0f));
        color = glm::vec4(139.0/255.0, 102.0/255.0, 71.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset5 -0.03f , 0.3f, -1.5f));
        model = glm::scale(model, glm::vec3(0.008f, 0.05f, 1.0f));
        color = glm::vec4(139.0/255.0, 102.0/255.0, 71.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }  
        //circle
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset5, 0.3f, -1.5f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
        color = glm::vec4(255.0/255.0, 255.0/255.0, 255.0/255.0, 1);
        for (int i = 1; i <= 4; i++) {
            if (i != 1) {
                model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
            }
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform4fv(uniformColor, 1, glm::value_ptr(color));
            meshList[2]->RenderMesh();
        }  
        //lid
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset5, -0.02f, -1.5f));
        model = glm::scale(model, glm::vec3(0.108f, 0.03f, 1.0f));
        color = glm::vec4(139.0/255.0, 102.0/255.0, 71.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();
        //body
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, -1.5f));
        model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
        color = glm::vec4(1.0f, 0.87843137f, 0.50980392f, 1.0f);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset5, -0.1f, -1.5f));
        model = glm::scale(model, glm::vec3(0.2f,0.7f, 1.0f));
        model = glm::rotate(model, 180 * toRadians,glm::vec3(0.0f, 0.0f, 1.0f));
        color = glm::vec4(235.0/255.0, 175.0/255.0, 76.0/255.0, 1);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(uniformColor, 1, glm::value_ptr(color));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        //end draw

        mainWindow.swapBuffers();
    }

    return 0;
}