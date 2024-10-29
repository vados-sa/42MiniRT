
#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>      // open, O_* constants
# include <unistd.h>     // close, read, write
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <string.h>     // strerror
# include <math.h>       // math functions (link with -lm)
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

//error messages
# define ALLOC_ERR "error on allocation"
# define ARGV_ERR "usage: ./minirt *.rt"
# define OPEN_ERR "file does not exist or cannot be opened"
# define EXTENSION_ERR "format *.rt required"
# define EMPTY_ERR "empty file"
# define QNT_ERR "capital letter elements can only be declared once in the scene"
# define INVALID_ERR "type identifier is not valid"

//macros
# define WIDTH 1200
# define HEIGHT 675

typedef struct s_coordinate
{
	float	x;
	float	y;
	float	z;
}	t_coordinate;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_A
{
	float	ratio;
	t_color	color;
}	t_A;

typedef struct s_C
{
	t_coordinate	view_point;
	t_coordinate	normal;
	float			fov;
}	t_C;

typedef struct s_L
{
	t_coordinate	point;
	float			brightness;
	t_color			color;
	struct t_L		*next; // check if necessary
}	t_L;

typedef struct s_plane
{
	t_coordinate	point;
	t_coordinate	normal;
	t_color			color;
}	t_plane;

typedef struct s_sphere
{
	t_coordinate	center;
	float			diameter;
	t_color			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_coordinate	center;
	t_coordinate	normal;
	float			diameter;
	float			height;
	t_color			color;
}	t_cylinder;

typedef struct s_object
{
	t_plane			*pl;
	t_sphere		*sp;
	t_cylinder		*cy;
	int				flag;
	struct t_object	*next;
}	t_object;

typedef struct s_scene
{
	t_A			a;
	t_C			c;
	t_L			*l;
	t_object	*objects;
}	t_scene;


typedef struct s_data
{
	mlx_t		*mlx_ptr;
	//mlx_image_t	*image;
	//t_scene		*scene;
	int			height;
	int			width;
	char		**lines;
}	t_data;

typedef void	(*t_mlx_keyfunc)(mlx_key_data_t keydata, void* param);

/*error-handling*/
void	ft_exit(int exit_code, t_data *data, char *message);
int		ft_return_int(int exit_code, t_data *data, char *message);
void	*ft_return_ptr(t_data *data, char *message);
void	free_content(t_data *data);

/*parsing*/
void	parse(t_data *data, char *filename);
void	read_file(char *filename, t_data *data);

#endif
