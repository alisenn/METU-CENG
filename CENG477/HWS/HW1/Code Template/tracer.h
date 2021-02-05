#ifndef TRACER_H
#define TRACER_H
#include "parser.h"
using namespace std;
using namespace parser;

Vec3f tracer(const Ray &r, const HitInfo &hitInfoResult,const Scene &s, const Camera &cam, int maxDepth);
#endif
