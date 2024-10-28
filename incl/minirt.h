
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

//macros
# define WIDTH 1200
# define HEIGHT 675

typedef struct s_data
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image;
}	t_data;

typedef void	(*t_mlx_keyfunc)(mlx_key_data_t keydata, void* param);

void	ft_exit(int exit_code, t_data *data, char *message);

#endif
