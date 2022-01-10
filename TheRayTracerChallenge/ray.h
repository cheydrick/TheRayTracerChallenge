#pragma once
#include "tuple.h"

struct Ray
{
	struct Tuple origin;
	struct Tuple direction;
};

int new_ray(struct Ray *ray, struct Tuple *origin, struct Tuple *direction)
{
	ray->origin = *origin;
	ray->direction = *direction;

	return 1;
}

int get_ray_origin(struct Tuple *origin, struct Ray* ray)
{
	*origin = ray->origin;

	return 1;
}

int get_ray_direction(struct Tuple *direction, struct Ray* ray)
{
	*direction = ray->direction;

	return 1;
}

int ray_position(struct Tuple *position, struct Ray *ray, float t)
{
	struct Tuple tmp_mult;
	mult_tuple_scalar(&tmp_mult, &ray->direction, t);

	add_tuples(position, &ray->origin, &tmp_mult);

	return 1;
}
