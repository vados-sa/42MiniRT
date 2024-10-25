#include <fcntl.h>      // open, O_* constants
#include <unistd.h>     // close, read, write
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // malloc, free, exit
#include <string.h>     // strerror
#include <math.h>       // math functions (link with -lm)
#include <mlx.h>        // MinilibX functions (install MinilibX library)
//#include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_data {
	void *mlx_ptr;
	void *win_ptr;
}	t_data;
