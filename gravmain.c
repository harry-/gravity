#include <GL/glut.h>

#include <stdio.h>
#include "gravity.h"


// object object1 = { 10, {4,0}, {1,2}};
// object objects[] = { {100000, {0,0}, {0,0}}, {100005, {50, 50}, {0,0}}, {100003, {25, 40}, {0,0}}};
object objects[OBJECTS];

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 1600.0, 0.0, 800.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	for(char i = 0; i<OBJECTS ;i++)
	{
		recalculateVectors(&objects[i]);	
		move(&objects[i]);
		displayObject(&objects[i]);

		glBegin(GL_POINTS);
			glVertex2i(objects[i].location.x,objects[i].location.y);
		glEnd();
	}

	/**
	glBegin(GL_LINES);
		glVertex2i(10,10);
		glVertex2i(100,100);
	glEnd();
	**/
	glFlush();
}

void main(int argc,char *argv[])
{
	// freopen("log", "w", stderr);
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1600, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("GRAVITY");
	init2D(0.0,0.0,0.0);

	initializeObjects();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();
}

