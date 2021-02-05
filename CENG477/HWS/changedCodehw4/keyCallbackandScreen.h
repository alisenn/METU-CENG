#ifndef KEYCALLBACKSCREEN_H
#define KEYCALLBACKSCREEN_H

#include "initialize.h"

extern unordered_map<int, bool> unOrdMap;
extern GLFWwindow* win ;

void screen() ;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) ;

#endif