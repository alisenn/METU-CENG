#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "glm/gtc/matrix_transform.hpp"
#include "helper.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

extern vector<GLuint> indexes;
extern int widthTexture, heightTexture;
extern int idxS;
extern mat4 projectionMatrix;

extern vec3 cam_g;
extern vec3 cam_pos;
extern vec3 cam_up;

void init();
void initHelper();
void initHelperHelper(int index);

#endif