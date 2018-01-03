#include <stdio.h>
#define G 6.67408E-11
#define OBJECTS 50
#define MAX_OBJECT_SIZE 1000000
#define MIN_OBJECT_SIZE 1
#define VIEW_WIDTH 1600
#define VIEW_HEIGHT 800
#define INITIAL_DIR_MAX 0
#define INITIAL_DIR_MIN 0 
#define COLLISION_DISTANCE 1

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
void collisions(object *object);

