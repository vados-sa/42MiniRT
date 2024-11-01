
#include "minirt.h"

void	our_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t*	pixel;

	//MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	//MLX_ASSERT(y < image->height, "Pixel is out of bounds");

	pixel = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	*(pixel++) = (uint8_t)((color >> 24));
	*(pixel++) = (uint8_t)((color >> 16));
	*(pixel++) = (uint8_t)((color >> 8));
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	draw_background(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	y = 0;
	color = 16711680;
	our_put_pixel(data->image, 600, 500, color);
	while (y < (uint32_t)IMAGE_HEIGHT)
	{
		x = 0;
		while (x < (uint32_t)IMAGE_WIDTH)
		{
			our_put_pixel(data->image, x, y, color);
			x++;
		}
		y++;
	}
}
