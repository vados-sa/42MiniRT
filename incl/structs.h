
#ifndef STRUCTS_H
# define STRUCTS_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "macros.h"

typedef float	t_float;

typedef void	(*t_keyfunc)(mlx_key_data_t keydata, void* param);
typedef void	(*t_hookfunc)(void* param);
typedef void	(*t_resizefunc)(int32_t width, int32_t height, void* param);

typedef enum e_dimension {
	CY_DIAM,
	CY_HEIGHT,
	SP_DIAM,
}	t_dimension;

typedef struct s_coord
{
	t_float	x;
	t_float	y;
	t_float	z;
}	t_coord;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_ray
{
	t_coord	origin;
	t_coord	direction;
}	t_ray;

typedef struct s_a
{
	t_float	ratio;
	t_color	color;
}	t_a;

typedef struct s_c
{
	t_coord		center;
	t_coord		orientation;
	t_coord		up;
	t_coord		right;
	t_float		fov;
}	t_c;

typedef struct s_l
{
	t_coord		point;
	t_float		brightness;
	t_color		color;
	struct s_l	*next;
}	t_l;

typedef struct s_plane
{
	t_coord		point;
	t_coord		normal;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_coord		center;
	t_float		radius;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_coord		center;
	t_coord		normal;
	t_float		radius;
	t_float		height;
	t_color		color;
	t_coord		top_end_cap;
	t_coord		bottom_end_cap;
	t_coord		cap_center;
	t_coord		cap_normal;
}	t_cylinder;

typedef struct s_intersec
{
	t_float		t;
	t_coord		point;
	t_coord		normal;
	t_color		color;
	char		type;
}	t_intersec;

typedef struct s_object
{
	char			type;
	t_plane			pl;
	t_sphere		sp;
	t_cylinder		cy;
	int				flag;
	t_intersec		temp;
	struct s_object	*next;
}	t_object;

typedef struct s_scene
{
	t_a			a;
	t_c			c;
	t_l			*l;
	t_object	*objects;
}	t_scene;

typedef struct s_vp
{
	t_float		width;
	t_float		height;
	t_coord		center;
	t_coord		up_left;
	t_coord		pixel_x;
	t_coord		pixel_y;
	t_coord		pixel00;
}	t_vp;

typedef struct s_data
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image;
	t_scene		*scene;
	t_float		image_height;
	t_float		image_width;
	char		**lines;
	t_vp		vp;
}	t_data;

#endif
