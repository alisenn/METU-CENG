#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sstream>
#include <chrono>
#include <GL/glew.h>
#include <GL/gl.h>   // The GL Header File
#include <GL/freeglut.h> // The GL Utility Toolkit (Glut) Header

// Experiments
// 1) Investigate the effect of transformations
// 2) Change projection to perspective
// 3) Change field of view of perspective projection
// 4) Change polygon mode to GL_LINE

char gRendererInfo[512] = { 0 };
char gWindowTitle[512] = { 0 };

int gWidth, gHeight;

void init() 
{
    glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glShadeModel(GL_FLAT);

}

void drawCubeBasic()
{
	glBegin(GL_TRIANGLES);
		// front face
	    glColor3f(1, 0, 0);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);

		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);

		// back face
	    glColor3f(0, 1, 0);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);

		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);

		// right face
	    glColor3f(0, 0, 1);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);

		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, 0.5);

		// left face
	    glColor3f(1, 1, 0);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, -0.5);

		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);

		// top face
	    glColor3f(1, 0, 1);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);

		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);

		// bottom face
	    glColor3f(0, 1, 1);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);

		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);

	glEnd();
}

void drawCubeArrays()
{
	static bool firstTime = true;

	if (firstTime)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		firstTime = false;
	}

	GLfloat vertexCol[] = {
		1, 0, 0, 1, 0, 0, 1, 0, 0, // front - red
		1, 0, 0, 1, 0, 0, 1, 0, 0, // front - red
		0, 1, 0, 0, 1, 0, 0, 1, 0, // back - green
		0, 1, 0, 0, 1, 0, 0, 1, 0, // back - green
		1, 1, 0, 1, 1, 0, 1, 1, 0, // left - yellow
		1, 1, 0, 1, 1, 0, 1, 1, 0, // left - yellow
		0, 0, 1, 0, 0, 1, 0, 0, 1, // right - blue
		0, 0, 1, 0, 0, 1, 0, 0, 1, // right - blue
		1, 0, 1, 1, 0, 1, 1, 0, 1, // top - magenta
		1, 0, 1, 1, 0, 1, 1, 0, 1, // top - magenta
		0, 1, 1, 0, 1, 1, 0, 1, 1, // bottom - cyan
		0, 1, 1, 0, 1, 1, 0, 1, 1, // bottom - cyan
	};

	GLfloat vertexPos[] = {
		// front - 1
		-0.5, -0.5,  0.5,
		 0.5, -0.5,  0.5,
		 0.5,  0.5,  0.5,
		// front - 2
		-0.5,  0.5,  0.5,
		-0.5, -0.5,  0.5,
		0.5,  0.5,  0.5,

		// back - 1
		-0.5, -0.5, -0.5,
		-0.5,  0.5, -0.5,
		0.5,  0.5, -0.5,
		// back - 2
		0.5, -0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5,  0.5, -0.5,

		// left - 1
		-0.5, -0.5,  0.5,
		-0.5,  0.5,  0.5,
		-0.5, -0.5, -0.5,
		// left - 2
		-0.5,  0.5,  0.5,
		-0.5,  0.5, -0.5,
		-0.5, -0.5, -0.5,

		// right - 1
		0.5,  0.5,  0.5,
		0.5, -0.5,  0.5,
		0.5, -0.5, -0.5,
		// right - 2
		0.5,  0.5, -0.5,
		0.5,  0.5,  0.5,
		0.5, -0.5, -0.5,

		// top - 1
		-0.5,  0.5,  0.5,
		0.5,  0.5,  0.5,
		-0.5,  0.5, -0.5,
		// top - 2
		0.5,  0.5,  0.5,
		0.5,  0.5, -0.5,
		-0.5,  0.5, -0.5,

		// bottom - 1
		-0.5, -0.5,  0.5,
		-0.5, -0.5, -0.5,
		0.5, -0.5,  0.5,
		// bottom - 2
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5,  0.5
	};

	glVertexPointer(3, GL_FLOAT, 0, vertexPos);
	glColorPointer(3, GL_FLOAT, 0, vertexCol);

	// At every frame, vertex and color data is copied from vertexPos
	// and vertexCol to GPU memory and the elements are drawn in
	// sequential order
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 / 3 = 12 triangles; 12 / 2 = 6 faces
}

void drawCubeElements()
{
	static bool firstTime = true;

	if (firstTime)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		firstTime = false;
	}

	GLuint indices[] = {
		0, 1, 2, // front
		3, 0, 2, // front
		4, 7, 6, // back
		5, 4, 6, // back
		0, 3, 4, // left
		3, 7, 4, // left
		2, 1, 5, // right
		6, 2, 5, // right
		3, 2, 7, // top
		2, 6, 7, // top
		0, 4, 1, // bottom
		4, 5, 1  // bottom
	};

	GLfloat vertexPos[] = {
		-0.5, -0.5,  0.5, // 0: bottom-left-front
		 0.5, -0.5,  0.5, // 1: bottom-right-front
		 0.5,  0.5,  0.5, // 2: top-right-front
		-0.5,  0.5,  0.5, // 3: top-left-front
		-0.5, -0.5, -0.5, // 4: bottom-left-back
		 0.5, -0.5, -0.5, // 5: bottom-right-back
		 0.5,  0.5, -0.5, // 6: top-right-back
		-0.5,  0.5, -0.5, // 7: top-left-back
	};

	GLfloat vertexCol[] = {
		1.0, 1.0, 1.0, // 0: unused
		0.0, 1.0, 1.0, // 1: bottom
		1.0, 0.0, 0.0, // 2: front
		1.0, 1.0, 1.0, // 3: unused
        1.0, 1.0, 0.0, // 4: left
		0.0, 0.0, 1.0, // 5: right
		0.0, 1.0, 0.0, // 6: back 
		1.0, 0.0, 1.0, // 7: top
	};

	glVertexPointer(3, GL_FLOAT, 0, vertexPos);
	glColorPointer(3, GL_FLOAT, 0, vertexCol);

	// At every frame, vertex and color data is copied from vertexPos
	// and vertexCol to GPU memory and the elements indicated by
	// indices are drawn
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
}

void drawCubeElementsVBO()
{
	static bool firstTime = true;

	static int vertexPosDataSizeInBytes;
	
	if (firstTime)
	{
		firstTime = false;

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		GLuint indices[] = {
			0, 1, 2, // front
			3, 0, 2, // front
			4, 7, 6, // back
			5, 4, 6, // back
			0, 3, 4, // left
			3, 7, 4, // left
			2, 1, 5, // right
			6, 2, 5, // right
			3, 2, 7, // top
			2, 6, 7, // top
			0, 4, 1, // bottom
			4, 5, 1  // bottom
		};

		GLfloat vertexPos[] = {
			-0.5, -0.5,  0.5, // 0: bottom-left-front
			0.5, -0.5,  0.5, // 1: bottom-right-front
			0.5,  0.5,  0.5, // 2: top-right-front
			-0.5,  0.5,  0.5, // 3: top-left-front
			-0.5, -0.5, -0.5, // 4: bottom-left-back
			0.5, -0.5, -0.5, // 5: bottom-right-back
			0.5,  0.5, -0.5, // 6: top-right-back
			-0.5,  0.5, -0.5, // 7: top-left-back
		};

		GLfloat vertexCol[] = {
			1.0, 1.0, 1.0, // 0: unused
			0.0, 1.0, 1.0, // 1: bottom
			1.0, 0.0, 0.0, // 2: front
			1.0, 1.0, 1.0, // 3: unused
			1.0, 1.0, 0.0, // 4: left
			0.0, 0.0, 1.0, // 5: right
			0.0, 1.0, 0.0, // 6: back 
			1.0, 0.0, 1.0, // 7: top
		};

		GLuint vertexAttribBuffer, indexBuffer;

		glGenBuffers(1, &vertexAttribBuffer);
		glGenBuffers(1, &indexBuffer);

		assert(vertexAttribBuffer > 0 && indexBuffer > 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexAttribBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		vertexPosDataSizeInBytes = sizeof(vertexPos);
		int vertexColDataSizeInBytes = sizeof(vertexCol);
		int indexDataSizeInBytes = sizeof(indices);
		
		glBufferData(GL_ARRAY_BUFFER, vertexPosDataSizeInBytes + vertexColDataSizeInBytes, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexPosDataSizeInBytes, vertexPos);
		glBufferSubData(GL_ARRAY_BUFFER, vertexPosDataSizeInBytes, vertexColDataSizeInBytes, vertexCol);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSizeInBytes, indices, GL_STATIC_DRAW);
	}

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(vertexPosDataSizeInBytes));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

typedef void(*drawFunc)(void);

void display()
{
	static int framesRendered = 0;
	static std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	glClearColor(0, 0, 0, 1);
	glClearDepth(1.0f);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	static float angle = 0;

	GLfloat deltaZ = -30;
	//GLfloat deltaZ = 0;

	//drawFunc drawCube = drawCubeBasic;
	//drawFunc drawCube = drawCubeArrays;
	//drawFunc drawCube = drawCubeElements;
	drawFunc drawCube = drawCubeElementsVBO;

	glLoadIdentity();
	glTranslatef(-6, -6, deltaZ);
	glRotatef(angle, 1, 0, 0);
	glScalef(5, 5, 5);
	drawCube();

	glLoadIdentity();
	glTranslatef(-6, 6, deltaZ);
	glRotatef(angle / 2, 0, 1, 0);
	glScalef(5, 5, 5);
	drawCube();

	glLoadIdentity();
	glTranslatef(6, 6, deltaZ);
	glRotatef(angle / 4, 0, 0, 1);
	glScalef(5, 5, 5);
	drawCube();

	glLoadIdentity();
	glTranslatef(6, -6, deltaZ);
	glRotatef(angle / 8, 1, 1, 0);
	glScalef(5, 5, 5);
	drawCube();

	angle += 5;

	glutSwapBuffers();
	++framesRendered;

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsedTime = end - start;
	if (elapsedTime.count() > 1.)
	{
		start = std::chrono::system_clock::now();

		std::stringstream stream;
		stream << framesRendered;
		framesRendered = 0;

		strcpy(gWindowTitle, gRendererInfo);
		strcat(gWindowTitle, " - ");
		strcat(gWindowTitle, stream.str().c_str());
		strcat(gWindowTitle, " FPS");

		glutSetWindowTitle(gWindowTitle);
	}
}

void reshape(int w, int h)   // Create The Reshape Function (the viewport)
{
    w = w < 1 ? 1 : w;
    h = h < 1 ? 1 : h;

    gWidth = w;
    gHeight = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10, 10, -10, 10, -10, 10);
	gluPerspective(45, (float) w / h, 1, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) 
    {
        case 27:     // Escape
            exit(0); 
            break; 
        default:  
            break;
    }
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv)   // Create Main Function For Bringing It All Together
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("");
	glewInit();

    strcpy(gRendererInfo, (const char*) glGetString(GL_RENDERER));
    strcat(gRendererInfo, " - ");
    strcat(gRendererInfo, (const char*) glGetString(GL_VERSION));
    glutSetWindowTitle(gRendererInfo);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}

