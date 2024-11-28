
#include "../incl/minirt.h"

/*Function to check intersection with the cap plane*/
static int	intersect_plane(t_ray ray, t_coord pl_point, \
							t_coord pl_normal, t_float *t)
{
	t_float	denom;
	t_coord	oc;

	denom = vec_dot(pl_normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		oc = vec_sub(pl_point, ray.origin);
		*t = vec_dot(oc, pl_normal) / denom;
		return (*t >= 0);
	}
	return (0);
}

/* Function to check if point is within the cylinder's radius */
static int	is_within_radius(t_coord point, t_coord center, t_float radius)
{
	t_coord	diff;

	diff = vec_sub(point, center);
	return (vec_dot(diff, diff) <= radius * radius);
}

t_intersec *intersect_single_cap(t_ray ray, t_object *obj, t_float t, \
								t_coord cap_center, t_coord cap_normal)
{
	t_coord	point;

	if (intersect_plane(ray, cap_center, cap_normal, &t))
	{
		point = ray_at(ray, t);
		if (is_within_radius(point, cap_center, obj->cy.radius))
		{
			obj->temp.t = t;
			obj->temp.point = point;
			obj->temp.color = obj->cy.color;
			obj->temp.normal = cap_normal;
			return (&obj->temp);
		}
	}
	return (NULL);
}

t_intersec *intersect_cap(t_ray ray, t_object *obj, t_float t)
{
	t_intersec	*result;

	result = intersect_single_cap(ray, obj, t, obj->cy.top_end_cap, \
					vec_mult(obj->cy.normal, -1));
	if (result)
	    return (result);
	result = intersect_single_cap(ray, obj, t, vec_add(obj->cy.top_end_cap, \
					vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.normal);
	if (result)
	    return (result);
	return (NULL);
}


/* static t_intersec	*intersect_top_cap(t_ray ray, t_object *obj, t_float t)
{
	t_coord	point;
	t_coord	diff;

	point = ray_at(ray, t);
	//printf("Point: (%f, %f, %f)\n", point.x, point.y, point.z);
    //printf("Top End Cap: (%f, %f, %f)\n", obj->cy.top_end_cap.x, obj->cy.top_end_cap.y, obj->cy.top_end_cap.z);
    //printf("Radius: %f\n", obj->cy.radius);
	if (is_within_radius(point, obj->cy.top_end_cap, obj->cy.radius))
	{
		obj->temp.t = t;
		obj->temp.point = ray_at(ray, t);
		obj->temp.color = obj->cy.color;
		obj->temp.normal = vec_mult(obj->cy.normal, -1);
		return (&obj->temp);
	}
	//printf("check TOP\n");
	return (NULL);
}

static t_intersec	*intersect_bottom_cap(t_ray ray, t_object *obj, t_float t)
{
	t_coord	point;

	point = ray_at(ray, t);
	if (is_within_radius(point, vec_add(obj->cy.top_end_cap, \
		vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.radius))
	{
		obj->temp.t = t;
		obj->temp.point = point;
		obj->temp.color = obj->cy.color;
		obj->temp.normal = obj->cy.normal;
		return (&obj->temp);
	}
	//printf("check BOTTOM\n");
	return (NULL);
}

t_intersec	*intersect_cap(t_ray ray, t_object *obj, t_float t)
{
	if (intersect_plane(ray, obj->cy.top_end_cap, \
		vec_mult(obj->cy.normal, -1), &t))
		return (intersect_top_cap(ray, obj, t));
	if (intersect_plane(ray, vec_add(obj->cy.top_end_cap, \
		vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.normal, &t))
		return (intersect_bottom_cap(ray, obj, t));
	return (NULL);
} */

/* t_intersec	*intersect_cap(t_ray ray, t_object *obj, t_float t) // I don't know how to divide this
{
	t_coord point;

	if (intersect_plane(ray, obj->cy.top_end_cap, \
		vec_mult(obj->cy.normal, -1), &t))
    {
        point = ray_at(ray, t);
        if (is_within_radius(point, obj->cy.top_end_cap, obj->cy.radius))
        {
            obj->temp.t = t;
            obj->temp.point = ray_at(ray, t);
            obj->temp.color = obj->cy.color;
            obj->temp.normal = vec_mult(obj->cy.normal, -1);
            return (&obj->temp);
        }
    }
    if (intersect_plane(ray, vec_add(obj->cy.top_end_cap, \
		vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.normal, &t))
    {
        point = ray_at(ray, t);
        if (is_within_radius(point, vec_add(obj->cy.top_end_cap, \
			vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.radius))
        {
            obj->temp.t = t;
            obj->temp.point = point;
            obj->temp.color = obj->cy.color;
            obj->temp.normal = obj->cy.normal;
            return (&obj->temp);
        }
    }
    return (NULL);
} */