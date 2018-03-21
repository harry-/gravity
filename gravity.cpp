#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "gravity.h"

#pragma warning(disable : 4996)

_Bool mybool = 1;

extern object objects[OBJECTS];

void move(object *object)
{
	object->location.x += object->direction.x * SPEED;
	object->location.y += object->direction.y * SPEED;
}

void displayObject(object *object)
{
	printf("displaying object of size %d\n", object->size);
	printf("x: %f, y: %f\n", object->location.x, object->location.y);
	printf("dirx: %f, diry: %f\n", object->direction.x, object->direction.y);
}

void debugObject(object *object)
{
	fprintf(stderr, "displaying object of size %d\n", object->size);
	fprintf(stderr, "x: %f, y: %f\n", object->location.x, object->location.y);
	fprintf(stderr, "dirx: %f, diry: %f\n", object->direction.x, object->direction.y);
}

void initializeObjects()
{
	srand(time(NULL));
	for (int i = 0; i<OBJECTS; i++)
	{
		objects[i].size = (rand() % MAX_OBJECT_SIZE)+1; 	
		objects[i].location.x = (rand() % (VIEW_WIDTH +1)) +SCREEN_WIDTH/2-VIEW_WIDTH/2;
		objects[i].location.y = (rand() % (VIEW_HEIGHT +1)) + SCREEN_HEIGHT/2-VIEW_HEIGHT/2;
		objects[i].direction.x = (rand() % (INITIAL_DIR_MAX-INITIAL_DIR_MIN +1))+INITIAL_DIR_MIN;
		objects[i].direction.y = (rand() % (INITIAL_DIR_MAX-INITIAL_DIR_MIN +1))+INITIAL_DIR_MIN;
	}
}

void recalculateVectors(object *object)
{
	for (char i = 0; i<OBJECTS;i++)
	{
		/* collisions are dealt with seperately 
		   and this also prevents the object attracting itself, hopefully */
		if (distance(object, &objects[i]) < COLLISION_DISTANCE ) 
			continue;
		recalculateVector(object, &objects[i]);
	}
}

char collisions(object *object)
{
	char collisionFlag = 0;
	for (char i = 0; i<OBJECTS;i++)
	{
		/* keep the object from colliding with itself */
		if (distance(object, &objects[i]) == 0 )
			continue;
		/* objects that are far apart, dont collide */
		if (distance(object, &objects[i]) >= COLLISION_DISTANCE)
			continue;
		collisionFlag = 1;
		if  (distance(object, &objects[i]) <= 0.5)
		collision(object, &objects[i]);	
	}
	return collisionFlag;
}

void collision(object *obj1, object *obj2)
{
	int newSize = obj1->size + obj2->size;
	struct vector newDirection = weightedVectorAddition(obj1->direction, obj1->size, obj2->direction, obj2->size);

	obj1->size = newSize;
	obj1->direction = newDirection; 	

	obj2->size = 0;
}

struct vector weightedVectorAddition(struct vector v1, int weight1, struct vector v2, int weight2)
{
	struct vector v;
	long weight = weight1 + weight2;
	v.x = v1.x*(weight1/weight) + v2.x*(weight2/weight) ;
	v.y = v1.y*(weight1/weight) + v2.y*(weight2/weight) ;
	return v;
}

void recalculateVector(object *object1, object *object2)
{
	struct vector attVector = attractionVector(object1, object2);
	object1->direction.x += attVector.x;
	object1->direction.y += attVector.y;
}

struct vector attractionVector(object *obj1, object *obj2)
{
	struct vector vector;

	#ifdef DEBUG
	fprintf (stderr, "calculating attaction vector for the following objects:\n");
	debugObject(obj1);
	debugObject(obj2);
	fprintf(stderr, "distance between these objects: %f\n", distance(obj1, obj2));
	#endif

	vector.x = obj2->location.x - obj1->location.x;
	vector.y = obj2->location.y - obj1->location.y;

	#ifdef DEBUG
	fprintf(stderr, "before unit vectorization: %f, %f\n", vector.x, vector.y);
	#endif

	vector = unitVector(vector);
	double gforce = force(obj1, obj2);

	#ifdef DEBUG
	fprintf(stderr, "before force multiplication: %f, %f\n", vector.x, vector.y);
	fprintf(stderr, "force: %f\n", gforce);
	#endif

	vector.x *= gforce;
	vector.y *= gforce; 

	#ifdef DEBUG
	fprintf(stderr, "attV x: %f, y: %f\n", vector.x, vector.y);
	#endif

	return vector;
}

struct vector unitVector(struct vector vector)
{
	double length = vectorLength(vector);
	struct vector unitVector;
	unitVector.x = vector.x/length;
	unitVector.y = vector.y/length;
	return unitVector;
}

double vectorLength(struct vector vector)
{
	double length = sqrt(pow(vector.x,2)+pow(vector.y,2));
	return length;
}

double distance (object *obj1, object *obj2)
{
	double distance = sqrt(pow(obj1->location.x-obj2->location.x,2)+pow(obj1->location.y-obj2->location.y,2)); 
	return distance;
}

double force (object *obj1, object *obj2)
{
	double force = G*(((long long)obj1->size*obj2->size)/pow(distance(obj1, obj2),2));
	return force;
}

struct vector vectorAB(object *obj1, object *obj2)
{
	struct vector vectorAB;
	vectorAB.x = obj2->location.x-obj1->location.x;
	vectorAB.y = obj2->location.y-obj1->location.y;
	return vectorAB;
}

char* printPoint (struct point *point)
{
	static char output[MAX_COORD_DIGITS*2+10];
	sprintf(output, "%.2f, %.2f", point->x, point->y);
	return output;
}

char* printVector (struct vector *vector)
{
	static char output[MAX_COORD_DIGITS*2+10];
	sprintf(output , "%.2f, %.2f", vector->x, vector->y);
	return output; 
}
