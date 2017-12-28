#include <stdio.h>

struct point {
	int x;
	int y;
};

struct vector {
	struct point start;
	struct point end;
};

struct body {
	int size;
	struct vector vector;
	int speed;
};


struct body move(struct body object);

void main()
{
	struct body ball = { 10, {{0,0}, {100, 100}}, 1};
	ball =	move(ball);
	printf("new x: %d\n", ball.vector.start.x);
}

struct body move(struct body object)
 {
	 if (object.vector.start.x != object.vector.end.x)
		object.vector.start.x += object.speed;
	if (object.vector.start.y != object.vector.end.y)
		 object.vector.start.y += object.speed;
	return object;
 }

