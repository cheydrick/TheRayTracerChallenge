#pragma once
#include "tuple.h"
#include "ray.h"

struct Sphere
{
	struct Tuple origin;
	float radius;
	int id;
};

int new_sphere(struct Sphere *sphere, struct Tuple *origin, float radius, int id)
{
	sphere->origin = *origin;
	sphere->radius = radius;
	sphere->id = id;

	return 1;
}

int intersect_sphere(struct Sphere* sphere, struct Ray* ray, float **t_intersections)
{
	// Calculate the discriminant
	struct Tuple vec_sphere_to_ray; subtract_tuples(&vec_sphere_to_ray, &ray->origin, &sphere->origin);

	float a = dot_product(&ray->direction, &ray->direction);
	float b = 2.0 * dot_product(&ray->direction, &vec_sphere_to_ray);
	float c = dot_product(&vec_sphere_to_ray, &vec_sphere_to_ray) - 1;

	float discriminant = (b * b) - (4.0 * a * c);

	if (discriminant < 0)
	{
		*t_intersections = NULL;
		return 0;
	}

	else
	{
		*t_intersections = (float*)malloc(sizeof(float) * 2);
		float t1 = ((-1.0 * b) - sqrt(discriminant)) / (2.0 * a);
		float t2 = ((-1.0 * b) + sqrt(discriminant)) / (2.0 * a);

		(*t_intersections)[0] = t1;
		(*t_intersections)[1] = t2;

		return 2;
	}

	return -1;
}
