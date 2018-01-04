#include <GL/glut.h>
#include <stdio.h>
#include "gravity.h"

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
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	for(char i = 0; i<OBJECTS ;i++)
	{
		recalculateVectors(&objects[i]);	
	//	collisions(&objects[i]);
		move(&objects[i]);
	//	displayObject(&objects[i]);

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
//	glutIdleFunc(display);
	
	glutMainLoop();
}

