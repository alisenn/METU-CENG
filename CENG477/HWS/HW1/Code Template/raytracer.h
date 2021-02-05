#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "parser.h"
using namespace std;
using namespace parser;

Vec3f cross(const Vec3f &a, const Vec3f &b);
double dot(const Vec3f &a, const Vec3f &b);
double length2(const Vec3f &v);
double length(const Vec3f &v);
Vec3f normalize(const Vec3f &v);
Vec3f add(const Vec3f &a, const Vec3f &b);
Vec3f subtract(const Vec3f &a, const Vec3f &b);
Vec3f mult(const Vec3f &a, double c);
Vec3f pointWise(const Vec3f &a, const Vec3f &b);
Vec3f intersectionPointFinder(const Ray &r, double t);
double distance(const Vec3f &a, const Vec3f &b);
Ray generateRay(int i, int j, Camera camera );
HitInfo collionCheckSphere(const Ray &r, const Sphere &s, const Scene &scene , int objId);
HitInfo triangleIntersection(const Ray &r,const Triangle &triangle, const Scene &scene,int objId);
HitInfo intersectionMesh(const Ray &r, const Scene &s, const Mesh &m, int objId);
bool isShadow(const HitInfo &hitInfoResult,const Scene &s,const Vec3f &lightVector);

#endif
