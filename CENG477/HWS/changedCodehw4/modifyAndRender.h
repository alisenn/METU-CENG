#ifndef MODIFYANDRENDER_H
#define MODIFYANDRENDER_H

#include "keyCallbackandScreen.h"

extern GLuint csMVPidMat;
extern GLuint camIdPos;
extern GLuint widText;
extern GLuint heigFac;
extern GLuint PlanDif;
extern GLuint LigPos;
extern vec3 LigPosVec;
extern GLfloat plandDifff;

void modify();
void render();
void mov();
void clearBuffer();
#endif