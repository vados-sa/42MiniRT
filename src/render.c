
#include "minirt.h"

void	render(t_data *data)
{
	int	x;
	int	y;

	data->image = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->image)
		ft_exit(1, data, ALLOC_ERR);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->image, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

