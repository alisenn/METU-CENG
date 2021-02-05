#include <iostream>
#include "tracer.h"
#include "raytracer.h"
using namespace std;
using namespace parser;

Vec3f tracer(const Ray &r, const HitInfo &hitInfoResult,const Scene &s, const Camera &cam, int maxDepth)
{

    int numberOfSpheres = s.spheres.size();
    int numberOfTriangles = s.triangles.size();
    int numberOfMeshes = s.meshes.size();

    float pixel1 = 0;
    float pixel2 = 0;
    float pixel3 = 0;

    Vec3f pixelColor;

    if(hitInfoResult.hitted)
    {

      pixelColor=pointWise(s.materials[hitInfoResult.material_id -1].ambient,s.ambient_light);

      int numLights = s.point_lights.size();
  		for(int l = 0; l < numLights; l++)
  		{
		    bool shadowFlag = false;

		    PointLight light = s.point_lights[l];
		    float ltc = distance(light.position, cam.position);
        if(isShadow(hitInfoResult,s,light.position))
          continue;

        int material_id = hitInfoResult.material_id;

        Vec3f diffuse, specular;

        float distanceSquare = distance(light.position,hitInfoResult.intersectionPoint);
        distanceSquare *= distanceSquare;
      	Vec3f irradiance;
        irradiance.x = light.intensity.x/distanceSquare;
        irradiance.y = light.intensity.y/distanceSquare;
        irradiance.z = light.intensity.z/distanceSquare;

      	Vec3f lightVector = subtract(light.position, hitInfoResult.intersectionPoint);
      	lightVector = normalize(lightVector);


      	float dotProd = dot(lightVector, hitInfoResult.surfaceNormal);
      	dotProd = (dotProd < 0 ) ?  0 : dotProd ;



        diffuse = pointWise( mult(s.materials[hitInfoResult.material_id -1].diffuse,dotProd),irradiance);
        pixelColor=add(pixelColor,diffuse);

        //calculating specular
      	Vec3f h = subtract(lightVector, r.b);
      	h = normalize(h);

        dotProd = dot(h, hitInfoResult.surfaceNormal);
        dotProd = (dotProd < 0 ) ?  0 : dotProd ;

        float exponent = s.materials[hitInfoResult.material_id -1].phong_exponent;
        specular = pointWise( mult(s.materials[hitInfoResult.material_id -1].specular,pow(dotProd,exponent)),irradiance);
        pixelColor=add(pixelColor,specular);

    	}

      bool mirrorfeature = false;
      Vec3f met = s.materials[hitInfoResult.material_id -1].mirror;
      if(met.x != 0 || met.y != 0 || met.z != 0) mirrorfeature = true;

      Vec3f yansitma;
      yansitma.x = 0;
      yansitma.y = 0;
      yansitma.z = 0;

      if(maxDepth > 0 && mirrorfeature)
      {
      	double wi = -2 * dot(r.b, hitInfoResult.surfaceNormal);
      	Vec3f nWi;
        nWi = normalize(add(mult(hitInfoResult.surfaceNormal,wi),r.b));

    		Vec3f wiEps;
        wiEps = mult(nWi,s.shadow_ray_epsilon);

        Ray refRay;
        refRay.a = add(hitInfoResult.intersectionPoint,wiEps);
        refRay.b = nWi;

        int tmin = 999999;
        double t;
        HitInfo hitedMin;
        hitedMin.hitted = false;

        for (int k=0;k<s.spheres.size();k++)
        {
          HitInfo hitinfo;

          hitinfo = collionCheckSphere(refRay,s.spheres[k],s,k);
          t=hitinfo.t_value;
          if(hitinfo.hitted && hitinfo.t_value>=0)
          {
            if (t<tmin)
            {
              tmin = t;
              hitedMin=hitinfo;
            }
          }
        }

        for (int k=0;k<s.triangles.size();k++)
        {
         HitInfo hitinfo;
         hitinfo = triangleIntersection(refRay,s.triangles[k],s,k);
         t=hitinfo.t_value;
         if (hitinfo.hitted && hitinfo.t_value>=0)
         {
           if (t<tmin)
           {
             tmin = t;
             hitedMin=hitinfo;
           }
         }
        }

        for( int ttnet = 0; ttnet< s.meshes.size(); ttnet++)
        {
         HitInfo hitinfo;
         hitinfo = intersectionMesh(refRay,s,s.meshes[ttnet],ttnet);
         t=hitinfo.t_value;
         if (hitinfo.hitted && hitinfo.t_value>=0)
         {
           if (t<tmin)
           {
             tmin = t;
             hitedMin=hitinfo;
           }
         }
        }

        //if(!(hitedMin.obj_id == hitInfoResult.obj_id && hitedMin.typeOfObj == hitInfoResult.typeOfObj))
        //{
            yansitma = tracer(refRay, hitedMin,s, cam, (maxDepth - 1));
        //}
        pixelColor = add(pixelColor,pointWise(yansitma,s.materials[hitInfoResult.material_id - 1].mirror));
 		  }
  	}
  	else
 	  {
      	pixelColor.x = s.background_color.x;
      	pixelColor.y = s.background_color.y;
      	pixelColor.z = s.background_color.z;
  	}

  	return pixelColor;
}
