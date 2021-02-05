#include "helper.h"
#include "glm/glm.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include "glm/gtc/matrix_transform.hpp"

using namespace std;
static GLFWwindow* win = NULL;
int widthWindow = 600, heightWindow = 600;

GLuint idProgramShader;
GLuint idFragmentShader;
GLuint idVertexShader;
GLuint idJpegTexture;
GLuint idMapTexture;
GLuint idMVPMatrix;
GLuint idCameraPosition;
GLuint idHeightFactor;
GLuint idWidthTexture;
GLuint idHeightTexture;
GLuint idPosition;
GLuint idPlaneDiff;
GLuint idLightPosition;

GLfloat planeDifference = 0.0f;
glm::vec3 lightPosition(0, 0, 0);

int widthTexture, heightTexture;
int indexes_size;

glm::mat4 projectionMatrix;
glm::mat4 viewingMatrix;
glm::mat4 modelingMatrix;
glm::vec3 camera_gaze(0, 0, 1);
glm::vec3 camera_pos(0, 0, 0);
glm::vec3 camera_up(0, 1, 0);

GLfloat heightFactor = 10.0f;

std::unordered_map<int, bool> states;
bool fullscreen = false;
int windowHeight = 600;
int windowWidth = 600;
int windowX = 0;
int windowY = 0;

float speed = 0.0f;

void init(){
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  idPosition = glGetAttribLocation(idProgramShader, "position");
  glEnableVertexAttribArray(idPosition);

  GLuint vertexAttribBuffer, indexBuffer;
  glGenBuffers(1, &vertexAttribBuffer);
  glGenBuffers(1, &indexBuffer);

  glBindBuffer(GL_ARRAY_BUFFER, vertexAttribBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

  int width = widthTexture;
  int height = heightTexture;
  std::vector<float> vertices;

  for (int i=0; i<=height; i++)
  {
    for (int j=0; j<=width; j++)
    {
      vertices.push_back(j);
      vertices.push_back(0);
      vertices.push_back(i);
    }
  }


  std::vector<GLuint> indexes;
  indexes.push_back(0);

  for (int j=0; j<height; j++)
  {
    for (int i=0; i<=width; i++)
    {
      if (i != width)
      {
        indexes.push_back((j+1) * (width+1) + i);
        indexes.push_back(j * (width+1) + i + 1);
      }
      else if (j != height - 1)
      {
        indexes.push_back((j+1) * (width+1) + i);
        indexes.push_back((j+1) * (width+1) + i);
        indexes.push_back((j) * (width+1) + i + 1);
        indexes.push_back((j) * (width+1) + i + 1);
      }
      else
      {
        indexes.push_back((j+1) * (width+1) + i);
      }
    }
  }

  indexes_size = indexes.size();

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_size * sizeof(indexes[0]), indexes.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(idPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

  float fovyRad = M_PI / 4;
  projectionMatrix = glm::perspective(fovyRad, 1.0f, 0.1f, 1000.0f);
  camera_pos = glm::vec3(widthTexture/2, widthTexture/10, -widthTexture/4);
  camera_up = glm::vec3(0, 1, 0);
  camera_gaze = glm::vec3(0, 0, 1);

}

void makeChanges()
{
  if (states[GLFW_KEY_R])
      heightFactor += 0.5;
  if (states[GLFW_KEY_F])
      heightFactor -= 0.5;

  if (states[GLFW_KEY_Q])
      planeDifference += 1.0;
  if (states[GLFW_KEY_E])
      planeDifference -= 1.0;

  if (states[GLFW_KEY_A] || states[GLFW_KEY_D])
  {
    const float const_angle = 0.5 * M_PI / 180.0;
    float angle = 0.0f;
    if (states[GLFW_KEY_A])
        angle += const_angle;
    if (states[GLFW_KEY_D])
        angle -= const_angle;
    auto left = glm::cross(camera_up, camera_gaze);
    auto rot_matrix = glm::rotate(glm::mat4(1.0), angle, camera_up);
    camera_gaze = glm::normalize(glm::vec3(rot_matrix * glm::vec4(camera_gaze, 0.0)));
  }
  if (states[GLFW_KEY_S] || states[GLFW_KEY_W])
  {
    const float const_angle = 0.5 * M_PI / 180.0;
    float angle = 0.0f;
    if (states[GLFW_KEY_W])
        angle -= const_angle;
    if (states[GLFW_KEY_S])
        angle += const_angle;
    auto left = glm::cross(camera_up, camera_gaze);
    auto rot_matrix = glm::rotate(glm::mat4(1.0), angle, left);
    camera_gaze = glm::normalize(glm::vec3(rot_matrix * glm::vec4(camera_gaze, 0.0)));
    camera_up = glm::cross(camera_gaze, left);
  }
  if (states[GLFW_KEY_Y])
      speed += 0.01;
  if (states[GLFW_KEY_H])
      speed -= 0.01;
  if (states[GLFW_KEY_X])
      speed = 0.0;
  if (states[GLFW_KEY_T])
      lightPosition = lightPosition + glm::vec3(0,5,0);
  if (states[GLFW_KEY_G])
      lightPosition = lightPosition + glm::vec3(0,-5,0);
  if (states[GLFW_KEY_UP])
      lightPosition = lightPosition + glm::vec3(0,0,5);
  if (states[GLFW_KEY_DOWN])
      lightPosition = lightPosition + glm::vec3(0,0,-5);
  if (states[GLFW_KEY_RIGHT])
      lightPosition = lightPosition + glm::vec3(5,0,0);
  if (states[GLFW_KEY_LEFT])
      lightPosition = lightPosition + glm::vec3(-5,0,0);
  if (states[GLFW_KEY_I]){
	  camera_gaze = glm::vec3(0, 0, 1);
    camera_pos = glm::vec3(widthTexture/2, widthTexture/10, -widthTexture/4);
	  speed = 0.0;
	  planeDifference = 0.0;
	  lightPosition.x = 0;
	  lightPosition.y = 0;
	  lightPosition.z = 0;
  }
  
}

void render()
{
  int width, height;
  glfwGetFramebufferSize(win, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  makeChanges();

  camera_pos += glm::normalize(camera_gaze) * speed;

  viewingMatrix = glm::lookAt(camera_pos, camera_gaze + camera_pos, camera_up);

  glUniform4f(idCameraPosition, camera_pos[0], camera_pos[1], camera_pos[2], 0);
  glUniform4f(idLightPosition, lightPosition[0], lightPosition[1], lightPosition[2], 0);
  glUniformMatrix4fv(idMVPMatrix, 1, GL_FALSE, &(projectionMatrix * viewingMatrix)[0][0]);
  glUniform1f(idHeightFactor, heightFactor);
  glUniform1f(idPlaneDiff, planeDifference);

  glUniform1i(idWidthTexture, widthTexture);
  glUniform1i(idHeightTexture, heightTexture);

  glDrawElements(GL_TRIANGLE_STRIP, indexes_size, GL_UNSIGNED_INT, 0);
}

void toggleFullscreen() {
  fullscreen = !fullscreen;
  GLFWmonitor *monitor;
  const GLFWvidmode *mode;
  if (fullscreen)
  {
      glfwGetWindowSize(win, &windowWidth, &windowHeight);
      glfwGetWindowPos(win, &windowX, &windowY);
      monitor = glfwGetPrimaryMonitor();
      mode = glfwGetVideoMode(monitor);
  }
  glfwSetWindowMonitor(
      win,
      fullscreen ? monitor : nullptr,
      fullscreen ? 0 : windowX,
      fullscreen ? 0 : windowY,
      fullscreen ? mode->width : windowWidth,
      fullscreen ? mode->height : windowHeight,
      fullscreen ? mode->refreshRate : 0
  );
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
       glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (action != GLFW_PRESS && action != GLFW_RELEASE)
        return;
    if (action == GLFW_PRESS) // Buttons without hold
    {
        switch (key)
        {
        case GLFW_KEY_P:
            toggleFullscreen();
            return;
        }
    }
    states[key] = action == GLFW_PRESS;
}


static void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Please provide height and texture image files!\n");
    exit(-1);
  }

  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); // This is required for remote
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); // This might be used for local

  win = glfwCreateWindow(widthWindow, heightWindow, "CENG477 - HW4", NULL, NULL);

  if (!win) {
      glfwTerminate();
      exit(-1);
  }
  glfwMakeContextCurrent(win);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

      glfwTerminate();
      exit(-1);
  }
  string a = "shader.vert";
  string b = "shader.frag";

  glfwSetKeyCallback(win, keyCallback);
  glEnable(GL_DEPTH_TEST);
  initShaders(idProgramShader,a,b);

  initTexture(argv[1], argv[2], &widthTexture, &heightTexture);

  idMVPMatrix = glGetUniformLocation(idProgramShader, "MVP");
  idHeightFactor = glGetUniformLocation(idProgramShader, "heightFactor");
  idWidthTexture = glGetUniformLocation(idProgramShader, "widthTexture");
  idHeightTexture = glGetUniformLocation(idProgramShader, "heightTexture");
  idCameraPosition = glGetUniformLocation(idProgramShader, "cameraPosition");
  idJpegTexture = glGetUniformLocation(idProgramShader, "rgbTexture");
  idMapTexture = glGetUniformLocation(idProgramShader, "mapTexture");

  idPlaneDiff = glGetUniformLocation(idProgramShader, "planeDifference");
  idLightPosition = glGetUniformLocation(idProgramShader, "lightPosition");


  glUseProgram(idProgramShader);
  

  glEnable(GL_CULL_FACE);
  init();
  //glUseProgram(idProgramShader);

  while(!glfwWindowShouldClose(win)) {
    render();
    glfwSwapBuffers(win);
    glfwPollEvents();
  }


  glfwDestroyWindow(win);
  glfwTerminate();
  return 0;
}
