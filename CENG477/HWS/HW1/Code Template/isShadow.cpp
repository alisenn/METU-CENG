#include <iostream>
#include "tracer.h"
#include "raytracer.h"
using namespace std;
using namespace parser;

bool isShadow(const HitInfo &hitInfoResult,const Scene &s,const Vec3f &lightVector)
{
  Vec3f epsilon;
  Vec3f wi = subtract(lightVector, hitInfoResult.intersectionPoint);
  wi = normalize(wi);

  epsilon = mult(wi,s.shadow_ray_epsilon);

  Ray rayShadow;
  rayShadow.a = add(hitInfoResult.intersectionPoint,epsilon);
  rayShadow.b = epsilon;

  HitInfo hitShadow;

  double tOfLight = subtract(lightVector, rayShadow.a).x / rayShadow.b.x;
  int sphereLength = s.spheres.size();
  int triangleLength = s.triangles.size();
  int meshLength = s.meshes.size();

  for(int i = 0; i < sphereLength; i++)
  {
      Sphere sphere = s.spheres[i];
      hitShadow = collionCheckSphere(rayShadow,sphere, s, i);

      if(hitShadow.hitted)
        if(tOfLight > hitShadow.t_value && hitShadow.t_value >= 0)
            return true;
  }


   for(int i = 0; i < triangleLength; i++)
   {
       Triangle tri = s.triangles[i];
       hitShadow = triangleIntersection(rayShadow,tri, s, i);

       if(hitShadow.hitted)
         if(tOfLight > hitShadow.t_value && hitShadow.t_value >= 0)
             return true;
   }

    for(int i = 0; i < triangleLength; i++)
    {
        Mesh mesh = s.meshes[i];
        hitShadow = intersectionMesh(rayShadow,s,mesh, i);

        if(hitShadow.hitted)
          if(tOfLight > hitShadow.t_value && hitShadow.t_value >= 0)
              return true;
    }

    return false;
}
