#include "../includes/cub3D.h"

static void ft_load_images(t_data *d)
{
	d->tex.mini_p = mlx_load_png("./textures/player.png");
	d->tex.mini_f = mlx_load_png("./textures/floor.png");
	d->tex.mini_w = mlx_load_png("./textures/wall.png");
	d->im.mini_p = mlx_texture_to_image(d->mlx, d->tex.mini_p);
	d->im.mini_f = mlx_texture_to_image(d->mlx, d->tex.mini_f);
	d->im.mini_w = mlx_texture_to_image(d->mlx, d->tex.mini_w);
	mlx_delete_texture(d->tex.mini_p);
	mlx_delete_texture(d->tex.mini_f);
	mlx_delete_texture(d->tex.mini_w);
}

void	ft_minimap(t_data *d)
{
	mlx_image_t	*minimap;
	int			i;
	int			j;
	int			len;
	int			x;
	int			y;

	ft_load_images(d);
	minimap = mlx_new_image(d->mlx, d->dim_map.x * TILE, d->dim_map.y * TILE);
	mlx_image_to_window(d->mlx, minimap, 0, 0);
	i = -1;
	x = 0;
	y = 0;
	while (++i < d->dim_map.y)
	{
		j = -1;
		len = (int)ft_strlen(d->map[i]);
		if (len == 0)
			break ;
		while (++j < len)
		{
			if (d->map[i][j] && d->map[i][j] == '0')
			{
				printf("hola\n");
//				mlx_image_to_window(d->mlx, d->im.minimap, j * TILE, i * TILE);
				mlx_put_pixel(minimap, j * TILE, i * TILE, 0xFFFFFFFF);
			}
		}
	}
}
