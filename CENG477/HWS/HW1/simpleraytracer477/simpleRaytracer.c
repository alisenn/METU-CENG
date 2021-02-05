#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define ABS(a) ((a)>0?(a):-1*(a))

typedef struct
{
	double x,y,z;
} Vec3;

Vec3 light;

typedef struct
{
	int r,g,b;
} Color;

typedef struct
{
	Vec3 a;
	Vec3 b;
} Ray;

typedef struct
{
	Vec3 center;
	double r;
	Color color;
} Sphere;

typedef struct
{
	Vec3 a,b,c;
	Color color;
} Triangle;

int numSpheres;
int numTriangles;

Sphere *spheres;
Triangle *triangles;

typedef struct 
{
	Vec3 pos;
	Vec3 gaze;
	Vec3 v;
	Vec3 u;
	double l,r,b,t;
	double d;
} Camera;



Camera cam;

int sizeX, sizeY;

double pixelW, pixelH;

double halfPixelW, halfPixelH;

char outFileName[80];

Color **image;

Vec3 cross(Vec3 a, Vec3 b)
{
	Vec3 tmp;
	
	tmp.x = a.y*b.z-b.y*a.z;
	tmp.y = b.x*a.z-a.x*b.z;
	tmp.z = a.x*b.y-b.x*a.y;
	
	return tmp;
}

double dot(Vec3 a, Vec3 b)
{
		return a.x*b.x+a.y*b.y+a.z*b.z;
}

double length2(Vec3 v)
{
	return (v.x*v.x+v.y*v.y+v.z*v.z);
}

double length(Vec3 v)
{
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

Vec3 normalize(Vec3 v)
{
	Vec3 tmp;
	double d;
	
	d=length(v);
	tmp.x = v.x/d;
	tmp.y = v.y/d;
	tmp.z = v.z/d;
	
	return tmp;
}

Vec3 add(Vec3 a, Vec3 b)
{
	Vec3 tmp;
	tmp.x = a.x+b.x;
	tmp.y = a.y+b.y;
	tmp.z = a.z+b.z;
	
	return tmp;
}

Vec3 mult(Vec3 a, double c)
{
	Vec3 tmp;
	tmp.x = a.x*c;
	tmp.y = a.y*c;
	tmp.z = a.z*c;
	
	return tmp;
}

double distance(Vec3 a, Vec3 b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

int equal(Vec3 a, Vec3 b)
{
	double e = 0.000000001;
	
	//printf("%lf %lf %f ----",ABS((a.x-b.x)),ABS((a.y-b.y)),ABS((a.z-b.z)));
	if ((ABS((a.x-b.x))<e) && (ABS((a.y-b.y))<e) && (ABS((a.z-b.z))<e))
		{ return 1;}
	else { return 0;}
}

void readScene(char *fName)
{
    FILE *f;
    int i;
    char line[80]={};
    f = fopen(fName,"r");
    
    fscanf(f,"%d",&numSpheres);
    spheres = (Sphere *)malloc(sizeof(Sphere)*numSpheres);

    for (i=0;i<numSpheres;i++)
    {
	    fscanf(f,"%lf %lf %lf", &(spheres[i].center.x),&(spheres[i].center.y),&(spheres[i].center.z));
	    fscanf(f,"%lf", &(spheres[i].r));
	    fscanf(f,"%d %d %d", &(spheres[i].color.r),&(spheres[i].color.g),&(spheres[i].color.b));
    }
}

void readCamera(char *fName)
{
    FILE *f;
    int i;
    char line[80]={};
    f = fopen(fName,"r");
    
    fscanf(f,"%lf %lf %lf",&cam.pos.x,&cam.pos.y,&cam.pos.z);
    fscanf(f,"%lf %lf %lf",&cam.gaze.x,&cam.gaze.y,&cam.gaze.z);
    fscanf(f,"%lf %lf %lf",&cam.v.x,&cam.v.y,&cam.v.z);
    
    cam.u = cross(cam.gaze,cam.v);
    
    cam.u = normalize(cam.u);
    
    cam.v = cross(cam.u,cam.gaze);
    cam.v = normalize(cam.v);
    
    cam.gaze = normalize(cam.gaze);
    
    fscanf(f,"%lf %lf %lf %lf",&cam.l,&cam.r,&cam.b,&cam.t);
    fscanf(f,"%lf",&cam.d);
    fscanf(f,"%d %d",&sizeX,&sizeY);
    
    fscanf(f,"%s",outFileName);
    
    // camera reading complete
    
    pixelW = (cam.r-cam.l)/(double)sizeX;
    halfPixelW = pixelW*0.5;
    
    pixelH = (cam.t-cam.b)/(double)sizeY;
    halfPixelH = pixelH*0.5;
    
    image = (Color **)malloc(sizeof(Color *)*sizeX);
    
    if (image==NULL)
    {
        printf("Cannot allocate memory for image.");
        exit(1);
    }
    
    for (i=0;i<sizeX;i++)
    {
        image[i] = (Color *)malloc(sizeof(Color)*sizeY);
        if (image[i]==NULL)
        {
            printf("Cannot allocate memory for image.");
            exit(1);
        }
    }
}

void initImage()
{
	int i,j;

    for (i=0;i<sizeX;i++)
		for (j=0;j<sizeY;j++)
		{
			image[i][j].r = 255;
			image[i][j].g = 255;
			image[i][j].b = 255;
		}
}

Ray generateRay(int i, int j)
{
	Ray tmp;
	
	Vec3 su,sv,s;
	
	tmp.a = cam.pos;
	
	su = mult(cam.u,cam.l+(i*pixelW)+halfPixelW);
	sv = mult(cam.v,cam.b+(j*pixelH)+halfPixelH);
	
	s = add(su,sv);
	
	tmp.b = add(mult(cam.gaze,cam.d),s);
    
	//printVec(add(tmp.a,tmp.b));
	
	return tmp;
}

    
double intersectSphere(Ray r, Sphere s)
{
	double A,B,C; //constants for the quadratic function
	
	double delta;
	
	Vec3 scenter;
    double sradius;
    
    Vec3 p;
		
	double t,t1,t2;
    int i;
	
    scenter = s.center;
    sradius = s.r;
    
    
	C = (r.a.x-scenter.x)*(r.a.x-scenter.x)+(r.a.y-scenter.y)*(r.a.y-scenter.y)+(r.a.z-scenter.z)*(r.a.z-scenter.z)-sradius*sradius;

	B = 2*r.b.x*(r.a.x-scenter.x)+2*r.b.y*(r.a.y-scenter.y)+2*r.b.z*(r.a.z-scenter.z);
	
	A = r.b.x*r.b.x+r.b.y*r.b.y+r.b.z*r.b.z;
	
	delta = B*B-4*A*C;
	
	if (delta<0) return -1;
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
		
		if (t1>=1.0) t = t1;
		else t = -1;
	}
	return t;
}

double intersectTriangle(Ray r, Triangle tr)
{
	double  a,b,c,d,e,f,g,h,i,j,k,l;
	double beta,gamma,t;
	
	double eimhf,gfmdi,dhmeg,akmjb,jcmal,blmkc;

	double M;
	
	double dd;
	Vec3 ma,mb,mc;

	ma = tr.a;
	mb = tr.b;
	mc = tr.c;
	
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
    if (M==0) return -1;
	
	t = -(f*akmjb+e*jcmal+d*blmkc)/M;
	
	if (t<1.0) return -1;
	
	gamma = (i*akmjb+h*jcmal+g*blmkc)/M;
	
	if (gamma<0 || gamma>1) return -1;
	
	beta = (j*eimhf+k*gfmdi+l*dhmeg)/M;
	
	if (beta<0 || beta>(1-gamma)) return -1;
	
	return t;
}

void writeImage(char *fileName)
{
	FILE *outFile;
	int i,j;
	
	outFile = fopen(fileName,"w");
	
	fprintf(outFile,"P3\n");
	fprintf(outFile,"# %s\n",fileName);
	
	fprintf(outFile,"%d %d\n",sizeX,sizeY);
	
	fprintf(outFile,"255\n");
	
	for (j=sizeY-1;j>=0;j--)
	{
		for (i=0;i<sizeX;i++)
		{
			fprintf(outFile,"%d %d %d ",image[i][j].r,image[i][j].g,image[i][j].b);
		}
		fprintf(outFile,"\n");
	}
	fclose(outFile);
}

int main(int argc, char **argv)
{
    char comm[200];
    int i,j,k;
    if (argc<3) {
	printf("Usage: raytracer <camera file> <scene file>\n");
	return 1;
    }
    readCamera(argv[1]);
    readScene(argv[2]);
    
    initImage();

    light.x = 0;
    light.y = 20;
    light.z = 0;

    for (i=0;i<sizeX;i++)
	    for (j=0;j<sizeY;j++)
	    {
		    Ray r;
		    double tmin = 40000;
		    int closestObj = -1;

		    r = generateRay(i,j);

		    for (k=0;k<numSpheres;k++)
		    {
			    double t;

			    t = intersectSphere(r,spheres[k]);

			    if (t>=1)
			    {
				    if (t<tmin)
				    {
					    tmin = t;
					    closestObj = k;
				    }
			    }
		    }
		    if (closestObj!=-1)
		    {
		    	Vec3 p;
			Vec3 normal;
			Vec3 toLight;
			double diffuse;
			p = add(r.a,mult(r.b,tmin));
			normal = add(p,mult(spheres[closestObj].center,-1));
			normal = normalize(normal);

			toLight = add(light,mult(p,-1));

			toLight = normalize(toLight);

			diffuse = dot(normal,toLight);
			if (diffuse<0) diffuse=0;

			image[i][j].r = spheres[closestObj].color.r*diffuse;
			image[i][j].g = spheres[closestObj].color.g*diffuse;
			image[i][j].b = spheres[closestObj].color.b*diffuse;
			image[i][j].r += spheres[closestObj].color.r*0.05;
			image[i][j].g += spheres[closestObj].color.g*0.05;
			image[i][j].b += spheres[closestObj].color.b*0.05;
		    }
	    }

    writeImage(outFileName);
    sprintf(comm,"convert %s %s.png",outFileName,outFileName);
    system(comm);
    
    return 0;
}
