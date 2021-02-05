#ifndef TRACER_H
#define TRACER_H
#include "parser.h"
using namespace std;
using namespace parser;

bool isShadow(const HitInfo &hitInfoResult,const Scene &s,const Vec3f &lightVector);
#endif
