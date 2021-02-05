#include "initialize.h"

GLuint positionIdForInit;
vector<float> vertices;

vector<GLuint> indexes;
int widthTexture, heightTexture,idxS;
vec3 cam_g(0, 0, 1);
vec3 cam_pos(0, 0, 0);
vec3 cam_up(0, 1, 0);
mat4 projectionMatrix;


void init(){

  GLuint VertexArrayID, vertAtBuf,indexBuffer;
  for (int i=0; i<=heightTexture; i++)
  {
    for (int j=0; j<=widthTexture; j++)
    {
      vertices.push_back(j);
      vertices.push_back(0);
      vertices.push_back(i);
    }
  }
  
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  positionIdForInit = glGetAttribLocation(idProgramShader, "position");
  glEnableVertexAttribArray(positionIdForInit);

  glGenBuffers(1, &vertAtBuf);
  glGenBuffers(1, &indexBuffer);

  glBindBuffer(GL_ARRAY_BUFFER, vertAtBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);


  initHelper();

  idxS = indexes.size();

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxS * sizeof(indexes[0]), indexes.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(positionIdForInit, 3, GL_FLOAT, GL_FALSE, 0, 0);

  float fovyRad = M_PI / 4;
  projectionMatrix = perspective(fovyRad, 1.0f, 0.1f, 1000.0f);
  cam_g = vec3(0, 0, 1);
  cam_pos = vec3(widthTexture/2, widthTexture/10, -widthTexture/4);
  cam_up = vec3(0, 1, 0);


}

void initHelper(){
  indexes.push_back(0);

  for (int j=0; j<heightTexture; j++)
  {
    initHelperHelper(j);
  }
}

void initHelperHelper(int index){
  int pluswidTex = widthTexture+1;
  for (int i=0; i<=widthTexture; i++)
  {
    if (i != widthTexture)
    {
      indexes.push_back((index+1) * (pluswidTex) + i);
      indexes.push_back(index * (pluswidTex) + i + 1);
    }
    else if (index+1 != heightTexture )
    {
      indexes.push_back((index+1) * (pluswidTex) + i);
      indexes.push_back((index+1) * (pluswidTex) + i);
      indexes.push_back((index) * (pluswidTex) + i + 1);
      indexes.push_back((index) * (pluswidTex) + i + 1);
    }
    else
    {
      indexes.push_back((index+1) * (pluswidTex) + i);
    }
  }
}