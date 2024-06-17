#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loader.hpp"
#include "shader.hpp"
#include "DataStructure.hpp"

GLFWwindow* window;

const int HEIGHT = 720;
const int WIDTH = 1240;

const char* title = "APPP COOL";
 

GLuint VAO;
GLuint verticesID;
GLuint normalsID;
GLuint programID;

glm::vec3 lightPos = glm::vec3(20.f, 3.f, 3.f);
glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f);
glm::vec3 objColor = glm::vec3(.2f, .5f, .5f);
glm::vec3 viewPos;

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

void handleInput(GLFWwindow* window);

void matrices_init(glm::mat4& model, glm::mat4& view, glm::mat4& projection);

void buffers_init();

void main_init();

void render_buffers();


int main(int argc, char const *argv[])
{
    main_init();

    matrices_init(model, view, projection);


    glClearColor(0.3, 0.3, 0.3, 1.0);

    buffers_init();

    load_model("../Room.blend");


    GLuint modelID = glGetUniformLocation(programID, "model");
    GLuint viewID = glGetUniformLocation(programID, "view");
    GLuint projectionID = glGetUniformLocation(programID, "projection");

    GLuint lightPosID = glGetUniformLocation(programID, "lightPos");
    GLuint lightColorID = glGetUniformLocation(programID, "lightColor");
    GLuint objColorID = glGetUniformLocation(programID, "objColor");
    GLuint viewPosID = glGetUniformLocation(programID, "viewPos");

    glUseProgram(programID);

    do {
        handleInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniform3f(lightPosID, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(lightColorID, lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(objColorID, objColor.x, objColor.y, objColor.z);
        glUniform3f(viewPosID, viewPos.x, viewPos.y, viewPos.z);

        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));


        render_buffers();

        glfwPollEvents();
        glfwSwapBuffers(window);

    } while (glfwWindowShouldClose(window) != GLFW_TRUE && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    return 0;
}

void main_init()
{
    // GLFW INIT
    if (!glfwInit()) {
        std::cerr << "FAILURE GLFW INIT\n";
        exit(-1);
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, title, 0, 0);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwMakeContextCurrent(window);
    // GLEW INIT
    if (glewInit() != GLEW_OK) {
        std::cerr << "FAILURE ON GLEW INIT\n";
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void buffers_init()
{
    programID = load_program("../media/cube/vertex", "../media/cube/frag");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

     
}

void render_buffers()
{
	glBindVertexArray(VAO);

	for(int i = 0; i < bufferSize; i++)
	{
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i].verticesID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[i].indicesID);

		glDrawElements(GL_TRIANGLES, buffers[i].verticesNum * 3, GL_UNSIGNED_INT, 0);

	};
};

void matrices_init(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, -5));

    viewPos = glm::vec3(0, 0, 3);
    view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    projection = glm::perspective(glm::radians(45.0f), 5.0f / 3.0f, 0.1f, 100.0f);
}

void handleInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        viewPos.x -= 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        viewPos.x += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        viewPos.y += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        viewPos.y -= 0.1f;
    }

    view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}
