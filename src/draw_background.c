
#include "minirt.h"

uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (b << 24 | g << 16 | r << 8 | a);
}

void	draw_background(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	y = 0;
	color = create_color(94, 4, 3, 255);
	while (y < IMAGE_HEIGHT)
	{
		x = 0;
		while (x < IMAGE_WIDTH)
		{
			mlx_put_pixel(data->image, x, y, color);
			x++;
		}
		y++;
	}
}
