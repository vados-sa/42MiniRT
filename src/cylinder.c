
#include "../incl/minirt.h"

static t_float	t_max_or_min(t_float a, t_float b, t_float discriminant)
{
	t_float	t_min;
	t_float	t_max;
	
	t_min = (-b - (sqrt(discriminant)) / 2 * a);
	t_max = (-b + (sqrt(discriminant)) / 2 * a);
	if (t_min >= 0)
		return (t_min);
	else if (t_max >= 0)
		return (t_max);
	else
		return (0);
}

t_intersec	*cylinder_intersect(t_ray ray, t_object *obj)
{
	t_float	discriminant;
	t_float	a;
	t_float	b;
	t_float	c;
	t_float	t;
	//t_coord	oc;
    t_coord	point;

	// For a cylinder aligned along the y-axis, the x and z components of the ray's direction are used.
	a = (ray.direction.x * ray.direction.x) +  (ray.direction.z * ray.direction.z);
	if (fabs(a) < 1e-6) // If a is approximately zero, it means the ray is parallel to the y-axis and won't intersect the cylinder's surface.
		return (NULL);
	//oc = vec_sub(ray.origin, obj->cy.center);
	b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
	//c = (oc.x * oc.x) +  (oc.z * oc.z) - (obj->cy.radius * obj->cy.radius);
	c = (ray.origin.x * ray.origin.x) +  (ray.origin.z * ray.origin.z) - 1; // The -1 accounts for the cylinder's radius being 1.
	discriminant = b * b - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	t = t_max_or_min(a, b, discriminant);
	if (t)
	{
		point = ray_at(ray, t);
        if (point.y < obj->cy.center.y - obj->cy.height || point.y > obj->cy.center.y + obj->cy.height)
            return (NULL); // Intersection is outside the finite cylinder's height
		obj->temp.t = t;
		obj->temp.point = point;
		obj->temp.normal = vec_unit(vec_sub(point, obj->cy.center));
		obj->temp.color = obj->cy.color;
		return (&obj->temp); 
	}
	return (NULL);
}
