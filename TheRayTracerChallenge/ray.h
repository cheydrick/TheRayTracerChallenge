#pragma once
#include "tuple.h"

struct Ray
{
	struct Tuple origin;
	struct Tuple direction;
};

struct Ray new_ray(struct Tuple origin, struct Tuple direction)
{
	struct Ray tmp_ray;
	tmp_ray.origin = origin;
	tmp_ray.direction = direction;

	return tmp_ray;
}

struct Tuple get_ray_origin(struct Ray* ray)
{
	return ray->origin;
}

struct Tuple get_ray_direction(struct Ray* ray)
{
	return ray->direction;
}