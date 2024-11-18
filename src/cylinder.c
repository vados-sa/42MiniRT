
#include "../incl/minirt.h"

static t_float	find_discriminant(t_ray ray, t_object *obj, t_float a, \
t_float b)
{
	t_float	c;

	c = vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), vec_sub(ray.origin, \
		obj->cy.top_end_cap)) - vec_dot(vec_sub(ray.origin, \
		obj->cy.top_end_cap), obj->cy.normal) * \
		vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), \
		obj->cy.normal) - obj->cy.radius * obj->cy.radius;
	return (b * b - 4 * a * c);
}

static t_float	find_t_cy(t_ray ray, t_object *obj)
{
	t_float	discriminant;
	t_float	a;
	t_float	b;
	t_float	t_max;
	t_float	t_min;

	a = vec_dot(ray.direction, ray.direction) - vec_dot(ray.direction, \
		obj->cy.normal) * vec_dot(ray.direction, obj->cy.normal);
	b = 2 * (vec_dot(ray.direction, vec_sub(ray.origin, obj->cy.top_end_cap)) - \
		vec_dot(ray.direction, obj->cy.normal) * vec_dot(vec_sub(ray.origin, \
		obj->cy.top_end_cap), obj->cy.normal));
	discriminant = find_discriminant(ray, obj, a, b);
	if (discriminant < 0)
		return (-1);
	t_min = ((-b - sqrt(discriminant))) / (2.0 * a);
	t_max = ((-b + sqrt(discriminant))) / (2.0 * a);
	if (t_min > t_max && t_min > 0)
		return (t_max);
	else if (t_min > 0)
		return (t_min);
	else if (t_max >= 0)
		return (t_max);
	else
		return (-1);
}

// Function to check intersection with a plane
int intersect_plane(t_ray ray, t_coord plane_point, t_coord plane_normal, t_float *t)
{
    t_float denom = vec_dot(plane_normal, ray.direction);
    if (fabs(denom) > 1e-6) // Avoid division by zero
    {
        t_coord p0l0 = vec_sub(plane_point, ray.origin);
        *t = vec_dot(p0l0, plane_normal) / denom;
        return (*t >= 0);
    }
    return 0;
}

// Function to check if point is within the cylinder's radius
int is_within_radius(t_coord point, t_coord center, t_float radius)
{
    t_coord diff = vec_sub(point, center);
    return (vec_dot(diff, diff) <= radius * radius);
}

t_intersec	*intersect_cap(t_ray ray, t_object *obj, t_float t)
{
	if (intersect_plane(ray, obj->cy.top_end_cap, vec_mult(obj->cy.normal, -1), &t))
    {
        t_coord point = ray_at(ray, t);
        if (is_within_radius(point, obj->cy.top_end_cap, obj->cy.radius))
        {
            obj->temp.t = t;
            obj->temp.point = ray_at(ray, t);
            obj->temp.color = obj->cy.color;
            obj->temp.normal = vec_mult(obj->cy.normal, -1);
            return (&obj->temp);
        }
    }
    if (intersect_plane(ray, vec_add(obj->cy.top_end_cap, vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.normal, &t))
    {
        t_coord point = ray_at(ray, t);
        if (is_within_radius(point, vec_add(obj->cy.top_end_cap, vec_mult(obj->cy.normal, obj->cy.height)), obj->cy.radius))
        {
            obj->temp.t = t;
            obj->temp.point = point;
            obj->temp.color = obj->cy.color;
            obj->temp.normal = obj->cy.normal;
            return (&obj->temp);
        }
    }
    return (NULL);
}

t_intersec	*cylinder_intersect(t_ray ray, t_object *obj)
{
	t_float	t;
	t_float	m;

	t = find_t_cy(ray, obj);
	if (t == -1)
		return (NULL);
	m = vec_dot(ray.direction, obj->cy.normal) * t + \
		vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), obj->cy.normal);
	/* if (m < 0 || m > obj->cy.height)
		return (NULL); */
	if (m < 0 || m > obj->cy.height)
		return (intersect_cap(ray, obj, t));
	obj->temp.t = t;
	obj->temp.point = ray_at(ray, obj->temp.t);
	obj->temp.color = obj->cy.color;
	obj->temp.normal = vec_unit(vec_sub(vec_sub(obj->temp.point, \
				obj->cy.top_end_cap), vec_mult(obj->cy.normal, m)));
	return (&obj->temp);
}
