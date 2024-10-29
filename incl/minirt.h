
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
# define ALLOC_ERR "Error\nerror on allocation"
# define ARGV_ERR "Error\nusage: ./minirt *.rt"
# define OPEN_ERR "Error\nfile does not exist or cannot be opened"
# define EXTENSION_ERR "Error\nformat *.rt required"
# define EMPTY_ERR "Error\nempty file"
# define TYPE_ID_ERR "Error\ntype identifier is not valid or cannot \
be declared more than once"
# define SPACE_ERR "Error\nspace at the end of the line"
# define LEN_ERR "Error\nelement doesn't contain the right amount of information"
# define RATIO_ERR "Error\nlight ratio invalid or out of bounds"
# define GEN_INFO_ERR "Error\nWrong amount of information"
# define COL_RANGE_ERR "Error\nrgb values are out of bounds"

//macros
# define WIDTH 1200
# define HEIGHT 675

typedef struct s_coordinate
{
	double	x;
	double	y;
	double	z;
}	t_coordinate;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_A
{
	double	ratio;
	t_color	color;
}	t_A;

typedef struct s_C
{
	t_coordinate	view_point;
	t_coordinate	normal;
	double			fov;
}	t_C;

typedef struct s_L
{
	t_coordinate	point;
	double			brightness;
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
	double			diameter;
	t_color			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_coordinate	center;
	t_coordinate	normal;
	double			diameter;
	double			height;
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
	mlx_image_t	*image;
	t_scene		*scene;
	int			height;
	int			width;
	char		**lines;
}	t_data;

typedef void	(*t_mlx_keyfunc)(mlx_key_data_t keydata, void* param);

/*init*/
int		parse_a(t_data *data, char *line);
void	init(t_data **data);

/*lists*/
t_object	*new_object_node(void);
void		add_object_node(t_object **light, t_object	*new);
t_object	*object_last_node(t_object *head);
t_L			*new_light_node(void);
t_L			*light_last_node(t_L *light);
void		add_light_node(t_L **light, t_L	*new);


/*error-handling*/
void	ft_exit(int exit_code, t_data *data, char *message);
void	free_content(t_data *data);

/*parsing*/
void	parse(t_data *data, char *filename);
void	read_file(char *filename, t_data *data);
ssize_t	ft_arr_len(char **arr);
char	**free_arr(char **arr1, char **arr2);
int		check_color(char *info, t_data *data, char type);
int		check_identifier(char *info, t_data *data, char *type);
int		float_check(char *info);
int		check_ratio(char *info, t_data *data, char type);
int		comma_count(char *info);
t_color	create_color(int r, int g, int b);

#endif
