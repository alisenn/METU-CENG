#include "modifyAndRender.h"
vec3 LigPosVec(0, 0, 0);
mat4 matrxView;
GLuint csMVPidMat,LigPos, camIdPos,PlanDif, widText, heigFac;
GLfloat plandDifff = 0.0;
GLfloat HeiFact = 10.0;
float velocity = 0.0;

void modify()
{
  float floAng,angle;
  if (unOrdMap[GLFW_KEY_R])
      HeiFact += 0.5;
  else if (unOrdMap[GLFW_KEY_Q])
      plandDifff += 1.0;
  else if (unOrdMap[GLFW_KEY_E])
      plandDifff -= 1.0;
  else if (unOrdMap[GLFW_KEY_F])
      HeiFact -= 0.5;
  else if (unOrdMap[GLFW_KEY_S] || unOrdMap[GLFW_KEY_W])
  {
    floAng = (0.5 * M_PI) / 180;
    angle = 0.0;
    if (unOrdMap[GLFW_KEY_S])
      angle += floAng;
    else if (unOrdMap[GLFW_KEY_W])
        angle -= floAng;

    auto left = cross(cam_up, cam_g);
    auto rmatx = rotate(mat4(1.0), angle, left);
    cam_g = normalize(vec3(rmatx * vec4(cam_g, 0.0)));
    cam_up = cross(cam_g, left);
  }
  else if ( unOrdMap[GLFW_KEY_D] ||  unOrdMap[GLFW_KEY_A])
  {
    floAng = (0.5 * M_PI) / 180;
    angle = 0.0;
    if (unOrdMap[GLFW_KEY_A])
        angle += floAng;
    else if (unOrdMap[GLFW_KEY_D])
        angle -= floAng;

    auto left = cross(cam_up, cam_g);
    auto rmatx = rotate(mat4(1.0), angle, cam_up);
    cam_g = normalize(vec3(rmatx * vec4(cam_g, 0.0)));
  }

  mov();
}

void mov(){
  vec3 t = vec3(0,5,0);
  vec3 g = vec3(0,-5,0);
  vec3 up = vec3(0,0,5);
  vec3 down = vec3(0,0,-5);
  vec3 right =vec3(5,0,0);
  vec3 left =  vec3(-5,0,0);
  if (unOrdMap[GLFW_KEY_Y])  velocity += 0.01;
  else if (unOrdMap[GLFW_KEY_UP])  LigPosVec = LigPosVec + up;
  else if (unOrdMap[GLFW_KEY_DOWN])   LigPosVec = LigPosVec + down;
  else if (unOrdMap[GLFW_KEY_RIGHT])  LigPosVec = LigPosVec + right;
  else if (unOrdMap[GLFW_KEY_LEFT])  LigPosVec = LigPosVec + left ;
  else if (unOrdMap[GLFW_KEY_H])  velocity -= 0.01;
  else if (unOrdMap[GLFW_KEY_X])  velocity = 0.0;
  else if (unOrdMap[GLFW_KEY_T])  LigPosVec = LigPosVec + t;
  else if (unOrdMap[GLFW_KEY_G])  LigPosVec = LigPosVec + g;

  else if (unOrdMap[GLFW_KEY_I]){
    cam_g = vec3(0, 0, 1);
    cam_pos = vec3(widthTexture/2, widthTexture/10, -widthTexture/4);
    velocity = 0.0;
    plandDifff = 0.0;
    LigPosVec.x = 0;
    LigPosVec.y = 0;
    LigPosVec.z = 0;
  }

}
void clearBuffer(){
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void render()
{
  int width, height;
  glfwGetFramebufferSize(win, &width, &height);
  glViewport(0, 0, width, height);
  clearBuffer();

  modify();

  cam_pos += normalize(cam_g) * velocity;

  matrxView = lookAt(cam_pos, cam_g + cam_pos, cam_up);
  glUniform4f(LigPos, LigPosVec[0], LigPosVec[1], LigPosVec[2], 0);

  glUniform4f(camIdPos, cam_pos[0], cam_pos[1], cam_pos[2], 0);
  glUniformMatrix4fv(csMVPidMat, 1, GL_FALSE, &(projectionMatrix * matrxView)[0][0]);
  glUniform1f(heigFac, HeiFact);
  glUniform1i(widText, widthTexture);
  glUniform1i(HeighttTexttId, heightTexture);
  glUniform1f(PlanDif, plandDifff);

  glDrawElements(GL_TRIANGLE_STRIP, idxS, GL_UNSIGNED_INT, 0);
}