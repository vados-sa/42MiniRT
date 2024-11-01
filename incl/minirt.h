
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
# define TYPE_ID_ERR "Error\nspace at the beginning of the line or \
type identifier is not valid or is declared more than once"
# define SPACE_ERR "Error\nspace at the end of the line"
# define LEN_ERR "Error\nelement doesn't contain the right amount of information"
# define RATIO_ERR "Error\nlight ratio invalid or out of bounds"
# define FOV_ERR "Error\nfov invalid or out of bounds"
# define GEN_INFO_ERR "Error\nwrong amount of information"
# define COL_RANGE_ERR "Error\nrgb values are out of bounds"
# define NORMAL_RANGE_ERR "Error\nnormal values are out of bounds"
# define NUM_ERR "Error\nnumber contains invalid characters"
# define DIMENSION_ERR "Error\nobject dimensions have to be positive values"

//macros
# define IMAGE_WIDTH 1200
# define IMAGE_HEIGHT 675
# define ASPECT_RATIO 1.77777777778
# define PI 3.14159265359
# define FOCAL_LENGTH 1.0

typedef enum e_dimension {
	CY_DIAM,
	CY_HEIGHT,
	SP_DIAM,
}	t_dimension;

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

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
	t_coord		center;
	t_coord		orientation;
	double		fov;
}	t_C;

typedef struct s_L
{
	t_coord		point;
	double		brightness;
	t_color		color;
	struct s_L	*next; // check if necessary
}	t_L;

typedef struct s_plane
{
	t_coord		point;
	t_coord		normal;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_coord		center;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_coord		center;
	t_coord		normal;
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_object
{
	char			type;
	t_plane			pl;
	t_sphere		sp;
	t_cylinder		cy;
	int				flag;
	struct s_object	*next;
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
	int			image_height;
	int			image_width;
	double		vp_width;
	double		vp_height;
	char		**lines;
}	t_data;

typedef void	(*t_mlx_keyfunc)(mlx_key_data_t keydata, void* param);

/*init*/
void		init(t_data **data);

/*lists*/
t_object	*new_object_node(void);
t_object	*object_last_node(t_object *head);
void		add_object_node(t_object **object, t_object	*new);
void		delete_object_list(t_object **objects);
t_L			*new_light_node(void);
t_L			*light_last_node(t_L *light);
void		add_light_node(t_L **light, t_L	*new);
void		delete_light_list(t_L **lights);


/*error-handling*/
void		ft_exit(int exit_code, t_data *data, char *message);
void		free_data(t_data *data);

/*utils*/
ssize_t		ft_arr_len(char **arr);
char		**free_arr(char **arr1, char **arr2);
char		**split_three(char *info);
int			float_check(char *info);
int			int_check(char *info);
t_color		col(int r, int g, int b);
t_coord		coord(double x, double y, double z);

/*parsing*/
void		parse(t_data *data, char *filename);
void		read_file(char *filename, t_data *data);
int			parse_a(t_data *data, char *line);
int			parse_l(t_data *data, char *line);
int			parse_c(t_data *data, char *line);
int			parse_cy(t_data *data, char *line);
int			parse_pl(t_data *data, char *line);
int			parse_sp(t_data *data, char *line);
int			check_color(char *info, t_data *data, char type);
int			check_identifier(char *info, t_data *data, char *type);
int			check_ratio(char *info, t_data *data, char type);
int			check_coordinates(char *info, t_data *data, char type);
int			check_normal(char *info, t_data *data, char type);
int			check_dimension(char *line, t_dimension type, t_data *data);
int			check_fov(char *info, t_data *data);

/*vector operations*/
double		vec_dot(t_coord v1, t_coord v2);
double		vec_len(t_coord v);
t_coord		vec_cross(t_coord v1, t_coord v2);
t_coord		vec_add(t_coord v1, t_coord v2);
t_coord		vec_sub(t_coord v1, t_coord v2);
t_coord		vec_mult(t_coord v1, double scalar);
t_coord		vec_unit(t_coord v);

#endif
