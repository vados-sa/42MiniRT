
#include "minirt.h"

void our_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)((color >> 24) & 0xFF);
	*(pixel++) = (uint8_t)((color >> 16) & 0xFF); // Red
	*(pixel++) = (uint8_t)((color >> 8) & 0xFF);  // Green
	*(pixel++) = (uint8_t)(color & 0xFF);         // Blue
}

//= Public =//

void	our_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t*	pixelstart;

	if (!image)
		ft_exit(1, NULL, NULL);
	//MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	//MLX_ASSERT(y < image->height, "Pixel is out of bounds");

	pixelstart = &image->pixels[(y * IMAGE_WIDTH + x) * sizeof(int32_t)];
	our_draw_pixel(pixelstart, color);
}

void	draw_background(void *param)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	t_data		*data;

	data = (t_data *)param;
	data->image = mlx_new_image(data->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!data->image)
		ft_exit(1, NULL, NULL);
	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		x = 0;
		while (x < IMAGE_WIDTH)
		{
			color = 0xFF0000;
			our_put_pixel(data->image, x, y, color);
			x++;
		}
		y++;
	}
}
