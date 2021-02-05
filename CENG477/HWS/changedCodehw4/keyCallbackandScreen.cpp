#include "keyCallbackandScreen.h"

bool fscreen = false;
int X = 0, Y=0 ,winWei=600, winHei=600;
//X = 0; Y = 0;
//winHei = 600;  winWei = 600;
GLFWwindow* win ;
unordered_map<int, bool> unOrdMap;


void screen() {
  fscreen = !fscreen;
  const GLFWvidmode *mode;
  GLFWmonitor *monitor;

  if (fscreen)
  {
      glfwGetWindowSize(win, &winWei, &winHei);
      glfwGetWindowPos(win, &X, &Y);
      monitor = glfwGetPrimaryMonitor();
      mode = glfwGetVideoMode(monitor);
  }
  GLFWmonitor *par1;
  int par2,par3,par4,par5,par6;
  if(fscreen){
    par1 = monitor;
    par2 = 0; par3 = 0; par4 = mode->width; par5 = mode->height; par6 = mode->refreshRate;
  }
  else{
    par1 = nullptr;
    par2 = X; par3 = Y; par4 =winWei; par5 =winHei; par6 = 0;
  }

  glfwSetWindowMonitor(win, par1,par2,par3,par4,par5,par6);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
       glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (action != GLFW_PRESS && action != GLFW_RELEASE)
        return;
    if (action == GLFW_PRESS) 
    {
        switch (key)
        {
        case GLFW_KEY_P:
            screen();
            return;
        }
    }
    unOrdMap[key] = action == GLFW_PRESS;
}
