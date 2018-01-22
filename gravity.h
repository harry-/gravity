#include <stdio.h>
#define G 6.67408E-11
#define SPEED 1000

#define LINUX 1
#define WINDOWS 2 

/* SYSTEM must be either windows or linux */
#define SYSTEM WINDOWS

//#define DEBUG 0
// #define SMALL
#define LARGE

#ifdef LARGE
#define OBJECTS 50 
#define MAX_OBJECT_SIZE 10000
#define MIN_OBJECT_SIZE 1 
#define VIEW_WIDTH 1500
#define VIEW_HEIGHT 900
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define MAX_COORD_DIGITS 5
#define TRACING
#endif

#ifdef SMALL
#define TRACING
#define OBJECTS 3 
#define MAX_OBJECT_SIZE 10000
#define MIN_OBJECT_SIZE 10000
#define VIEW_WIDTH 100
#define VIEW_HEIGHT 100
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define MAX_COORD_DIGITS 5
#endif

#ifdef DEBUG
#define OBJECTS 2
#define MAX_OBJECT_SIZE 1000000
#define MIN_OBJECT_SIZE 800000
#define VIEW_WIDTH 25
#define VIEW_HEIGHT 25
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define MAX_COORD_DIGITS 5
#endif

#define INITIAL_DIR_MAX 0
#define INITIAL_DIR_MIN 0 
#define COLLISION_DISTANCE 5

struct point {
	double x;
	double y;
};

struct vector {
	double x;
	double y; 
};

typedef struct object {
	int size;
	struct point location;
	struct vector direction;
}object;

void move(object *object);
void displayObject(object *object);
void recalculateVectors(object *object);
double distance(object *obj1, object *obj2);
double force (object *obj1, object *obj2);
double recalculateVector(object *object1, object *object2);
void test_force();
void test_distance();
struct vector attractionVector(object *obj1, object *obj2);
double vectorLength(struct vector vector);
void test_vectorLength();
void test_unitVector(float x, float y);
struct vector unitVector(struct vector vector);
void initializeObjects();
char collisions(object *object);
struct vector vectorAB(object *obj1, object *obj2);
char* printPoint (struct point *point);
char* printVector (struct vector *vector);
void test_vectorCalculations();
char* printPointB (struct point *point);
void collision(object *obj1, object *obj2);
struct vector weightedVectorAddition(struct vector vector1, int weight1, struct vector vector2, int weight2);
