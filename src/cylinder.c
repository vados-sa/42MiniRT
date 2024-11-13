
#include "../incl/minirt.h"

/* t_coord local_normal_at(t_coord point, t_object *obj, t_float m)
{
    t_coord normal;
    normal = vec_sub(point, vec_add(obj->cy.center, vec_mult(obj->cy.normal, m)));
    return vec_unit(normal);
} */

static t_float find_discriminant(t_ray ray, t_object *obj, t_float a, t_float b)
{
    t_float c;

    c = vec_dot(vec_sub(ray.origin, obj->cy.center), vec_sub(ray.origin, \
        obj->cy.center)) - vec_dot(vec_sub(ray.origin, obj->cy.center), \
        obj->cy.normal) * vec_dot(vec_sub(ray.origin, obj->cy.center),\
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
    b = 2 * (vec_dot(ray.direction, vec_sub(ray.origin, obj->cy.center)) - \
        vec_dot(ray.direction, obj->cy.normal) * vec_dot(vec_sub(ray.origin, \
        obj->cy.center), obj->cy.normal));
    discriminant = find_discriminant(ray, obj, a, b);
    if (discriminant < 0)
        return (-1);
    t_min = ((-b - sqrt(discriminant))) / (2.0 * a);
    t_max = ((-b + sqrt(discriminant))) / (2.0 * a);
    if (t_min > t_max && t_min > 0)
        return (t_max);
    else if (t_min >= 0) // maybe t_min > 0, not sure yet. t = 0 means that the intersection happens on the origin. Should something be redered or not?
        return (t_min);
    else if (t_max >= 0)
        return (t_max);
    else
        return (-1); // so this might be 0 ?
}

t_intersec *cylinder_intersect(t_ray ray, t_object *obj)
{
    t_float t;
    t_float m;
    
    t = find_t_cy(ray, obj);
    if (t == -1)
        return (NULL);
    m = vec_dot(ray.direction, obj->cy.normal) * t + \
        vec_dot(vec_sub(ray.origin, obj->cy.center), obj->cy.normal);
    if (m < 0 || m > obj->cy.height)
        return (NULL);
    obj->temp.t = t;
	obj->temp.point = ray_at(ray, obj->temp.t);
	obj->temp.color = obj->cy.color;
    //intersec.normal = local_normal_at(point, obj, m);
    return (&obj->temp);
}

/* t_intersec *cylinder_intersect(t_ray ray, t_object *obj) // copilot version
{
    t_float a, b, c, discriminant, t1, t2, t;
    t_coord point;
    t_intersec intersec;
    t_coord X = vec_sub(ray.origin, obj->cy.center);
    t_float D_dot_V = vec_dot(ray.direction, obj->cy.normal);
    t_float X_dot_V = vec_dot(X, obj->cy.normal);

    // Calculate the coefficients of the quadratic equation
    a = vec_dot(ray.direction, ray.direction) - D_dot_V * D_dot_V;
    b = 2 * (vec_dot(ray.direction, X) - D_dot_V * X_dot_V);
    c = vec_dot(X, X) - X_dot_V * X_dot_V - obj->cy.radius * obj->cy.radius;

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return NULL;

    t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 > t2)
    {
        t_float temp = t1;
        t1 = t2;
        t2 = temp;
    }

    // Check if the closest intersection point is within the cylinder's height
    t_float m1 = D_dot_V * t1 + X_dot_V;
    t_float m2 = D_dot_V * t2 + X_dot_V;

    if (t1 >= 0 && m1 >= 0 && m1 <= obj->cy.height)
    {
        t = t1;
    }
    else if (t2 >= 0 && m2 >= 0 && m2 <= obj->cy.height)
    {
        t = t2;
    }
    else
    {
        return NULL;
    }

    point = ray_at(ray, t);
    intersec.t = t;
    intersec.point = point;
    //intersec.normal = local_normal_at(point, obj, (t == t1) ? m1 : m2);
    intersec.color = obj->cy.color;

    obj->temp = intersec; // Store the intersection in the object's temp field
    return (&obj->temp);
} */
