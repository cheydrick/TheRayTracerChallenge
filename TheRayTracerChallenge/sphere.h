#pragma once
#include "tuple.h"
#include "ray.h"

struct Sphere
{
	struct Tuple origin;
	float radius;
	int id;
};

struct Sphere new_sphere(struct Tuple origin, float radius, int id)
{
	struct Sphere tmp_sphere;
	tmp_sphere.origin = origin;
	tmp_sphere.radius = radius;
	tmp_sphere.id = id;

	return tmp_sphere;
}

int intersect(struct Sphere* sphere, struct Ray* ray, float *t_intersections)
{
	// CODE

	// TEMP WHILE WRITING TESTS
	t_intersections = NULL;
	return -1;
}