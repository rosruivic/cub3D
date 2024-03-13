#include "../includes/cub3D.h"

static void	ft_background(t_data *d)
{
	int	i;
	int	j;

	d->im.background = mlx_new_image(d->mlx, W, H);
	mlx_image_to_window(d->mlx, d->im.background, 0, 0);
	i = -1;
	j = -1;
	while (++i < H)
	{
		j = -1;
		while (++j < H)
		{
			if (j < H / 2)
				mlx_put_pixel(d->im.background, i, j, d->hex_c);
			else
				mlx_put_pixel(d->im.background, i, j, d->hex_f);
		}
	}
}

void	ft_graphic(t_data *d)
{
	d->mlx = mlx_init(H, W, "Cubilete", false);
	ft_background(d);
	ft_minimap(d);
	// ft_raycasting(d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
}
