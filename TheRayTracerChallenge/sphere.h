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

int intersect(struct Sphere* sphere, struct Ray* ray, float **t_intersections)
{
	// Calculate the discriminant
	struct Tuple vec_sphere_to_ray = subtract_tuples(ray->origin, sphere->origin);

	float a = dot_product(ray->direction, ray->direction);
	float b = 2.0 * dot_product(ray->direction, vec_sphere_to_ray);
	float c = dot_product(vec_sphere_to_ray, vec_sphere_to_ray) - 1;

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
