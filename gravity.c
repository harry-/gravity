#include <stdio.h>
#include <math.h>
#include "gravity.h"
extern object objects[OBJECTS];

void move(object *object)
{
	object->location.x += object->direction.x;
	object->location.y += object->direction.y;
}

void displayObject(object *object)
{
	printf("displaing object of size %d\n", object->size);
	printf("x: %f, y: %f\n", object->location.x, object->location.y);
	printf("dirx: %f, diry: %f\n", object->direction.x, object->direction.y);
}

void debugObject(object *object)
{
	fprintf(stderr, "displaing object of size %d\n", object->size);
	fprintf(stderr, "x: %f, y: %f\n", object->location.x, object->location.y);
	fprintf(stderr, "dirx: %f, diry: %f\n", object->direction.x, object->direction.y);
}

void recalculateVectors(object *object)
{
	for (char i = 0; i<OBJECTS;i++)
	{
		if(object->location.x==objects[i].location.x&&object->location.y==objects[i].location.y)
			continue;
		recalculateVector(object, &objects[i]);
		fprintf(stderr, "object index %d\n", i);
	}
}

double recalculateVector(object *object1, object *object2)
{
	struct vector attVector = attractionVector(object1, object2);
	object1->direction.x += attVector.x;
	object1->direction.y += attVector.y;
}

struct vector attractionVector(object *obj1, object *obj2)
{
	struct vector vector;
	fprintf (stderr, "calculating attaction vector for the following objects:\n");
	debugObject(obj1);
	debugObject(obj2);
	vector.x = obj2->location.x - obj1->location.x;
	vector.y = obj2->location.y - obj1->location.y;
	fprintf(stderr, "before unit vectorization: %f, %f\n", vector.x, vector.y);
	vector = unitVector(vector);
	double gforce = force(obj1, obj2);
	fprintf(stderr, "before force multiplication: %f, %f\n", vector.x, vector.y);
	vector.x *= gforce;
	vector.y *= gforce; 
	fprintf(stderr, "attV x: %f, y: %f\n", vector.x, vector.y);
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

void test_unitVector(float x, float y)
{
	struct vector vector = {x,y};
	struct vector uVector = unitVector(vector);
	printf("the unit vector of %f, %f is: %f, %f\n", x, y, uVector.x, uVector.y);
}
void test_vectorLength()
{
	struct vector vector = {3,4};
	printf("length of vector 3,4: %f\n", vectorLength(vector));
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
	double force = G*((obj1->size*obj2->size)/pow(distance(obj1, obj2),2));
	return force;
}


void test_distance()
{
	object obj1 = {10, {1,1}, {0,0}};
	object obj2 = {10, {4,5}, {0,0}};
	printf("distance between 0,0 and 3,4: %f\n", distance(&obj1, &obj2));
}

void test_force()
{
	object obj1 = {100000, {1,1}, {0,0}};
	object obj2 = {100000, {4,5}, {0,0}};
	printf("force between 0,0 and 3,4: %.20f\n", force(&obj1, &obj2));
}
