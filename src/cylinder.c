
#include "../incl/minirt.h"

// D = ray.direction
// V = obj->cy.normal
// C = obj->cy.top_end_cap

/* t_coord local_normal_at(t_coord point, t_object *obj, t_float m)
{
    t_coord normal;
    normal = vec_sub(point, vec_add(obj->cy.center, vec_mult(obj->cy.normal, m)));
    return vec_unit(normal);
} */

static t_float find_discriminant(t_ray ray, t_object *obj, t_float a, t_float b)
{
    t_float c;

    c = vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), vec_sub(ray.origin, \
        obj->cy.top_end_cap)) - vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), \
        obj->cy.normal) * vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap),\
        obj->cy.normal) - obj->cy.radius * obj->cy.radius;
    return (b * b - 4 * a * c);
}

static t_float find_t_cy(t_ray ray, t_object *obj)
{
    t_float discriminant;
    t_float a;
    t_float b;
    t_float t_max;
    t_float t_min;

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
    else if (t_min > 0) // maybe t_min > 0, not sure yet. t = 0 means that the intersection happens on the origin. Should something be redered or not?
        return (t_min);
    else if (t_max >= 0)
        return (t_max);
    else
        return (-1); // so this might be 0 ?
}

/* t_float intersect_plane(t_ray ray, t_coord point, t_coord normal)
{
    t_float denom = vec_dot(normal, ray.direction);
    if (fabs(denom) > 1e-6)
    {
        t_float t = vec_dot(vec_sub(point, ray.origin), normal) / denom;
        if (t >= 0)
            return t;
    }
    return -1;
}

t_float caps(t_ray ray, t_object *obj, t_float t)
{
    t_float top_cap;
    t_float bottom_cap;
    t_coord top_center;
    t_coord bottom_center;
    t_coord p;

    top_center = vec_add(obj->cy.top_end_cap, vec_mult(obj->cy.normal, obj->cy.height));
    bottom_center = obj->cy.top_end_cap;
    top_cap = intersect_plane(ray, bottom_center, obj->cy.normal);
    bottom_cap = intersect_plane(ray, top_center, vec_mult(obj->cy.normal, -1));
    if (top_cap >= 0 && top_cap < t)
    {
        p = ray_at(ray, top_cap);
        if (vec_dot(vec_sub(p, top_center), vec_sub(p, top_center)) <= obj->cy.radius * obj->cy.radius)
            return top_cap;
    }
    if (bottom_cap >= 0 && bottom_cap < t)
    {
        p = ray_at(ray, bottom_cap);
        if (vec_dot(vec_sub(p, bottom_center), vec_sub(p, bottom_center)) <= obj->cy.radius * obj->cy.radius)
            return bottom_cap;
    }
    return t;
} */

t_intersec *cylinder_intersect(t_ray ray, t_object *obj)
{
    t_float t;
    t_float m;
    
    t = find_t_cy(ray, obj);
    if (t == -1)
        return (NULL);
    m = vec_dot(ray.direction, obj->cy.normal) * t + \
        vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), obj->cy.normal);
    if (m < 0 || m > obj->cy.height)
        return (NULL);
    /* if (m < 0 || m > obj->cy.height)
        t = caps(ray, obj, t); */
    obj->temp.t = t;
	obj->temp.point = ray_at(ray, obj->temp.t);
	obj->temp.color = obj->cy.color;
    //obj->temp.normal = local_normal_at(obj->temp.point, obj, m);
    obj->temp.normal = vec_unit(vec_sub(obj->cy.center, obj->temp.point));
    return (&obj->temp);
}
