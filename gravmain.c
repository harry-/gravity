
#include <stdio.h>
#include "gravity.h"

#if SYSTEM == WINDOWS
#include "glut.h"
#elif SYSTEM == LINUX
#include <GL/glut.h>
#endif



char tracing = 1;

#if (DEBUG == 2)
/* object objects[] =	{{100000, {1,5}, {0,0}}, 
			{100000, {4,9}, {0,0}},	
			{100000, {4,1}, {0,0}} };*/
object objects[] =	{{10000, {792,401}, {0,0}}, 
			{10000, {793,391}, {0,0}} };
#else
object objects[OBJECTS];
#endif

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 1600.0, 0.0, 800.0);
}

void oneStepInTime()
{
	if (!tracing)
		glClear(GL_COLOR_BUFFER_BIT);
	
	for(char i = 0; i<OBJECTS ;i++)
	{
		if (objects[i].size == 0)
			continue;
		char collision = 0;
		glColor3f(1.0, 0.0, 0.0);
		recalculateVectors(&objects[i]);
		collision = collisions(&objects[i]);
		move(&objects[i]);
	//	displayObject(&objects[i]);

//		if (objects[i].size > MAX_OBJECT_SIZE -(MAX_OBJECT_SIZE-MIN_OBJECT_SIZE)*0.75)
//			glColor3f(1.0, 0.0, 0.0);
//		if(i == 1)
//			glColor3f(0.0, 1.0, 0.0);
		if(collision)
			glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POINTS);
			glVertex2i(objects[i].location.x,objects[i].location.y);
		glEnd();
	}

	glFlush();
}

void display()
{
	oneStepInTime();
}

void anyKey(unsigned char key, int x, int y)
{
	extern char tracing;
	if (key == 't')
	{
		printf("%d", tracing);
		tracing ^= 1;
		printf("%d", tracing);
	}
	oneStepInTime();
}

void main(int argc,char *argv[])
{
	freopen("log", "w", stderr);
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1600, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("GRAVITY");
	init2D(0.0,0.0,0.0);
	
	#if (DEBUG != 2)
	initializeObjects();
	#endif

	glutKeyboardFunc(anyKey);
	glutDisplayFunc(display);
	#ifndef DEBUG
	glutIdleFunc(display);
	#endif	
	glutMainLoop();
}

