#include "initialize.h"
#include "modifyAndRender.h"
#include "keyCallbackandScreen.h"
using namespace std;

int widthWindow = 600, heightWindow = 600;

GLuint idMapTexture;

void callStartUp(char *argv[],string str1,string str2){
  glfwSetKeyCallback(win, keyCallback);
  glEnable(GL_DEPTH_TEST);
  initShaders(idProgramShader,str1,str2);
  initTexture(argv[1], argv[2], &widthTexture, &heightTexture);
}

void maininIcindekimain(char *argv[]){
  string svert = "shader.vert";
  string sfrag = "shader.frag";

  callStartUp(argv,svert,sfrag);

  csMVPidMat = glGetUniformLocation(idProgramShader, "MVP");
  camIdPos = glGetUniformLocation(idProgramShader, "camIdPos");
  heigFac = glGetUniformLocation(idProgramShader, "HeiFact");
  widText = glGetUniformLocation(idProgramShader, "widthTexture");
  HeighttTexttId = glGetUniformLocation(idProgramShader, "heightTexture");
  camIdPos = glGetUniformLocation(idProgramShader, "camIdPos");
  idJpegTexture = glGetUniformLocation(idProgramShader, "rgbTexture");
  idMapTexture = glGetUniformLocation(idProgramShader, "mapTexture");

  PlanDif = glGetUniformLocation(idProgramShader, "plandDifff");
  LigPos = glGetUniformLocation(idProgramShader, "LigPosVec");

  glUseProgram(idProgramShader);
  //initTexture(argv[1], argv[2], &widthTexture, &heightTexture);

  glEnable(GL_CULL_FACE);
  init();

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
  maininIcindekimain(argv);

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
