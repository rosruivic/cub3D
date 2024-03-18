#include "../includes/cub3D.h"

static void	ft_load_images(t_data *d)
{
	d->tex.mini_p = mlx_load_png("./textures/player.png");
	d->tex.mini_f = mlx_load_png("./textures/floor.png");
	d->tex.mini_w = mlx_load_png("./textures/wall.png");
	d->tex.mini_r = mlx_load_png("./textures/ray.png");
	d->im.mini_p = mlx_texture_to_image(d->mlx, d->tex.mini_p);
	d->im.mini_f = mlx_texture_to_image(d->mlx, d->tex.mini_f);
	d->im.mini_w = mlx_texture_to_image(d->mlx, d->tex.mini_w);
	d->im.mini_r = mlx_texture_to_image(d->mlx, d->tex.mini_r);
	mlx_delete_texture(d->tex.mini_p);
	mlx_delete_texture(d->tex.mini_f);
	mlx_delete_texture(d->tex.mini_w);
	//	mlx_delete_texture(d->tex.mini_r);
}

void	ft_move_minimap(t_data *d)
{
	mlx_delete_image(d->mlx, d->im.mini_r);
	d->im.mini_p->instances[0].y = (int)d->ply.pos.y * TILE;
	d->im.mini_p->instances[0].x = (int)d->ply.pos.x * TILE;
	printf("HOla\n");
	d->im.mini_r = mlx_texture_to_image(d->mlx, d->tex.mini_r);
	ft_calc_vector(d);
	// (void)d;
}

void	ft_minimap(t_data *d)
{
	int	i;
	int	j;
	int	len;

	ft_load_images(d);
	i = -1;
	while (++i < d->dim_map.y)
	{
		j = -1;
		len = (int)ft_strlen(d->map[i]);
		if (len == 0)
			break ;
		while (++j < len)
		{
			if (d->map[i][j] && (d->map[i][j] == '0' || d->map[i][j] == 'N'
					|| d->map[i][j] == 'S' || d->map[i][j] == 'W'
					|| d->map[i][j] == 'E'))
				mlx_image_to_window(d->mlx, d->im.mini_f, j * TILE, i * TILE);
			if (d->map[i][j] && d->map[i][j] == '1')
				mlx_image_to_window(d->mlx, d->im.mini_w, j * TILE, i * TILE);
		}
	}
	mlx_image_to_window(d->mlx, d->im.mini_p, (int)d->ply.pos.x * TILE,
			(int)d->ply.pos.y * TILE);
	ft_calc_vector(d);
}
