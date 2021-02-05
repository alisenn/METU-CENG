#include <iostream>
#include "parser.h"
#include "tracer.h"
#include "ppm.h"

using namespace std;
using namespace parser;

Vec3f cross(const Vec3f &a, const Vec3f &b)
{
	Vec3f tmp;

	tmp.x = a.y*b.z-b.y*a.z;
	tmp.y = b.x*a.z-a.x*b.z;
	tmp.z = a.x*b.y-b.x*a.y;

	return tmp;
}

double dot(const Vec3f &a, const Vec3f &b)
{
		return a.x*b.x+a.y*b.y+a.z*b.z;
}

double length2(const Vec3f &v)
{
	return (v.x*v.x+v.y*v.y+v.z*v.z);
}

double length(const Vec3f &v)
{
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

Vec3f normalize(const Vec3f &v)
{
	Vec3f tmp;
	double d;

	d=length(v);
	tmp.x = v.x/d;
	tmp.y = v.y/d;
	tmp.z = v.z/d;

	return tmp;
}

Vec3f add(const Vec3f &a, const Vec3f &b)
{
	Vec3f tmp;
	tmp.x = a.x+b.x;
	tmp.y = a.y+b.y;
	tmp.z = a.z+b.z;

	return tmp;
}
Vec3f subtract(const Vec3f &a, const Vec3f &b)
{
	Vec3f tmp;
	tmp.x = a.x-b.x;
	tmp.y = a.y-b.y;
	tmp.z = a.z-b.z;

	return tmp;
}
Vec3f mult(const Vec3f &a, double c)
{
	Vec3f tmp;
	tmp.x = a.x*c;
	tmp.y = a.y*c;
	tmp.z = a.z*c;

	return tmp;
}
Vec3f pointWise(const Vec3f &a, const Vec3f &b)
{
	Vec3f tmp;
	tmp.x = a.x*b.x;
	tmp.y = a.y*b.y;
	tmp.z = a.z*b.z;

	return tmp;
}
Vec3f intersectionPointFinder(const Ray &r, double t)
{
	Vec3f result;
	result.x = r.a.x + t*r.b.x;
	result.y = r.a.y + t*r.b.y;
	result.z = r.a.z + t*r.b.z;

	return result;
}
double distance(const Vec3f &a, const Vec3f &b)
{
		return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

Ray generateRay(int i, int j, Camera camera )
{
	Vec3f gaze = normalize(camera.gaze);

	double l = camera.near_plane.x;
	double r = camera.near_plane.y;
	double b = camera.near_plane.z;
	double t = camera.near_plane.w;

	double su = (r - l)*(j + 0.5)/camera.image_width;
	double sv = (t - b)*(i + 0.5)/camera.image_height;

	Vec3f m, q, u, v, s;

	m=add(camera.position,mult(gaze,camera.near_distance));
	u = cross(gaze, camera.up);
	u = normalize(u);
	v = cross(u, gaze);

	q=add(add(m,mult(u,l)),mult(v,t));

  s= add(q,subtract(mult(u,su),mult(v,sv)));

	Ray ray;
	ray.a = camera.position;
	ray.b = subtract(s, camera.position);
	ray.b = normalize(ray.b);

	return ray;
}

HitInfo collionCheckSphere(const Ray &r, const Sphere &s, const Scene &scene , int objId)
{
	double A,B,C;

	double delta;
	HitInfo hitinfo;
	Vec3f scenter;
  double sradius;

  Vec3f p;

	double t,t1,t2;
  int i;

  scenter = scene.vertex_data[s.center_vertex_id-1];
  sradius = s.radius;


	C = (r.a.x-scenter.x)*(r.a.x-scenter.x)+(r.a.y-scenter.y)*(r.a.y-scenter.y)+(r.a.z-scenter.z)*(r.a.z-scenter.z)-sradius*sradius;

	B = 2*r.b.x*(r.a.x-scenter.x)+2*r.b.y*(r.a.y-scenter.y)+2*r.b.z*(r.a.z-scenter.z);

	A = r.b.x*r.b.x+r.b.y*r.b.y+r.b.z*r.b.z;

	delta = B*B-4*A*C;

	if (delta<0)
	{
		hitinfo.hitted = false;

		return hitinfo;
	}
	else if (delta==0)
	{
		t = -B / (2*A);
	}
	else
	{
		double tmp;
		delta = sqrt(delta);
		A = 2*A;
		t1 = (-B + delta) / A;
		t2 = (-B - delta) / A;

		if (t2<t1){
			tmp = t2;
			t2 = t1;
			t1 = tmp;
		}
		t=t1;
	}
	hitinfo.intersectionPoint = intersectionPointFinder(r, t);
	hitinfo.surfaceNormal = subtract(hitinfo.intersectionPoint, scenter);
	hitinfo.surfaceNormal = normalize(hitinfo.surfaceNormal);
	hitinfo.material_id = s.material_id;
	hitinfo.hitted = true;
	hitinfo.typeOfObj = "sphere";
	hitinfo.obj_id = objId;
	hitinfo.t_value = t;

	return hitinfo;
}

HitInfo triangleIntersection(const Ray &r,const Triangle &triangle, const Scene &scene,int objId)
{
	HitInfo hitinfo;
	hitinfo.hitted = false;

	double  a,b,c,d,e,f,g,h,i,j,k,l;
	double beta,gamma,t;

	double eimhf,gfmdi,dhmeg,akmjb,jcmal,blmkc;

	double M;

	double dd;
	Vec3f ma,mb,mc;
	ma=scene.vertex_data[triangle.indices.v0_id-1];
	mb=scene.vertex_data[triangle.indices.v1_id-1];
	mc=scene.vertex_data[triangle.indices.v2_id-1];

	a = ma.x-mb.x;
	b = ma.y-mb.y;
	c = ma.z-mb.z;

	d = ma.x-mc.x;
	e = ma.y-mc.y;
	f = ma.z-mc.z;

	g = r.b.x;
	h = r.b.y;
	i = r.b.z;

	j = ma.x-r.a.x;
	k = ma.y-r.a.y;
	l = ma.z-r.a.z;

	eimhf = e*i-h*f;
	gfmdi = g*f-d*i;
	dhmeg = d*h-e*g;
	akmjb = a*k-j*b;
	jcmal = j*c-a*l;
	blmkc = b*l-k*c;

	M = a*eimhf+b*gfmdi+c*dhmeg;
    if (M==0) return hitinfo;

	t = -(f*akmjb+e*jcmal+d*blmkc)/M;

	if (t<1.0) return hitinfo;

	gamma = (i*akmjb+h*jcmal+g*blmkc)/M;

	if (gamma<0 || gamma>1) return hitinfo;

	beta = (j*eimhf+k*gfmdi+l*dhmeg)/M;

	if (beta<0 || beta>(1-gamma)) return hitinfo;

	hitinfo.hitted = true;
	hitinfo.typeOfObj = "triangle";
	hitinfo.obj_id = objId;
	hitinfo.material_id = triangle.material_id;
	hitinfo.t_value = t;
	hitinfo.intersectionPoint = intersectionPointFinder(r, t);
	hitinfo.surfaceNormal = cross(subtract(mb, ma), subtract(mc, ma));
	hitinfo.surfaceNormal = normalize(hitinfo.surfaceNormal);

	return hitinfo;
}

HitInfo intersectionMesh(const Ray &r, const Scene &s, const Mesh &m, int objId)
{
	HitInfo hitInfo;
  HitInfo hitInfoResult;
	hitInfoResult.hitted = false;
  Triangle tri;
  float min = 99999999;

	for(int i = 0; i < m.faces.size(); i++)
	{

    tri.material_id = m.material_id;
    tri.indices = m.faces[i];

		hitInfo = triangleIntersection(r, tri, s, objId);
		if(hitInfo.hitted && hitInfo.t_value >= 0)
		{
      if(hitInfo.t_value <= min){
        min = hitInfo.t_value;
        hitInfoResult = hitInfo;
      }
			hitInfo.typeOfObj = "mesh";
		}
	}
	return hitInfoResult;
}


int main(int argc, char* argv[])
{

    Scene scene;

    scene.loadFromXml(argv[1]);
		double t;

		for(int c=0;c<scene.cameras.size();c++)
		{
			int index=0;
			unsigned char* image = new unsigned char [scene.cameras[c].image_width * scene.cameras[c].image_height * 3];
			for (int i=0;i<scene.cameras[c].image_height;i++)
		    {

					for (int j=0;j<scene.cameras[c].image_width;j++)
			    {

				    Ray r;
				    double tmin = 40000;
				    int closestObj = -1;
            HitInfo hitedMin;
            hitedMin.hitted=false;
				    r = generateRay(i,j,scene.cameras[c]);

				    for (int k=0;k<scene.spheres.size();k++)
				    {
					    HitInfo hitinfo;

					    hitinfo = collionCheckSphere(r,scene.spheres[k],scene,k);
							t=hitinfo.t_value;
					    if (hitinfo.hitted && hitinfo.t_value>=0)
					    {
						    if (t<tmin)
						    {
							    tmin = t;
							    closestObj = k;
                  hitedMin=hitinfo;
						    }
					    }
				    }

						for (int k=0;k<scene.triangles.size();k++)
					  {
						 HitInfo hitinfo;

						 hitinfo = triangleIntersection(r,scene.triangles[k],scene,k);
						 t=hitinfo.t_value;
						 if (hitinfo.hitted && hitinfo.t_value>=0)
						 {
							 if (t<tmin)
							 {
								 tmin = t;
								 closestObj = k;
                 hitedMin=hitinfo;
							 }
						 }
					 }
           for( int ttnet = 0; ttnet< scene.meshes.size(); ttnet++){
             HitInfo hitinfo;

             hitinfo = intersectionMesh(r,scene,scene.meshes[ttnet],ttnet);
             t=hitinfo.t_value;
             if (hitinfo.hitted && hitinfo.t_value>=0)
             {
               if (t<tmin)
               {
                 tmin = t;
                 closestObj = ttnet;
                 hitedMin=hitinfo;

               }
             }
           }

            Vec3f pixelColor = tracer(r,hitedMin,scene,scene.cameras[c],scene.max_recursion_depth);
            if(pixelColor.x> 255)
              image[index++] = 255;
            else
              image[index++] = round(pixelColor.x);
            if(pixelColor.y> 255)
              image[index++] = 255;
            else
              image[index++] = round(pixelColor.y);
            if(pixelColor.z> 255)
              image[index++] = 255;
            else
              image[index++] = round(pixelColor.z);
			    }
			}
			write_ppm(scene.cameras[c].image_name.c_str(), image, scene.cameras[c].image_width, scene.cameras[c].image_height);
		}
}
