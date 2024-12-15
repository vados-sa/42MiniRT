#include "minirt.h"

t_matrix3x3 rotation_matrix(t_coord axis, float angle)
{
    t_matrix3x3 matrix;
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    float one_minus_cos_a = 1.0 - cos_a;

    matrix.m[0][0] = cos_a + axis.x * axis.x * one_minus_cos_a;
    matrix.m[0][1] = axis.x * axis.y * one_minus_cos_a - axis.z * sin_a;
    matrix.m[0][2] = axis.x * axis.z * one_minus_cos_a + axis.y * sin_a;

    matrix.m[1][0] = axis.y * axis.x * one_minus_cos_a + axis.z * sin_a;
    matrix.m[1][1] = cos_a + axis.y * axis.y * one_minus_cos_a;
    matrix.m[1][2] = axis.y * axis.z * one_minus_cos_a - axis.x * sin_a;

    matrix.m[2][0] = axis.z * axis.x * one_minus_cos_a - axis.y * sin_a;
    matrix.m[2][1] = axis.z * axis.y * one_minus_cos_a + axis.x * sin_a;
    matrix.m[2][2] = cos_a + axis.z * axis.z * one_minus_cos_a;

    return matrix;
}

t_coord apply_rotation(t_coord vec, t_matrix3x3 matrix)
{
    t_coord result;

    result.x = vec.x * matrix.m[0][0] + vec.y * matrix.m[0][1] + vec.z * matrix.m[0][2];
    result.y = vec.x * matrix.m[1][0] + vec.y * matrix.m[1][1] + vec.z * matrix.m[1][2];
    result.z = vec.x * matrix.m[2][0] + vec.y * matrix.m[2][1] + vec.z * matrix.m[2][2];

    return result;
}
