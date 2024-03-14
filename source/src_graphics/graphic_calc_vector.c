#include "../includes/cub3D.h"

void	ft_calc_vector(t_data *d)
{
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	double	step_x;
	double	side_x;
	double	step_y;
	double	side_y;
	int		hit;
	int		wall_side;
	int		i;
	double	cam_x;

	side_x = 0;
	side_y = 0;
	i = -1;
	while (++i < W)
	{
		hit = 0;
		cam_x = 2 * i / (double)W - 1;
		map_x = (int)d->ply.pos.x;
		map_y = (int)d->ply.pos.y;
		ray_dir_x = d->ply.dir.x + d->ply.cam.x * cam_x;
		ray_dir_y = d->ply.dir.y + d->ply.cam.y * cam_x;
		if (ray_dir_x != 0)
			delta_x = fabs(1 / ray_dir_x);
		else
			delta_x = 1e30;
		if (ray_dir_y != 0)
			delta_y = fabs(1 / ray_dir_y);
		else
			delta_y = 1e30;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_x = ((d->ply.pos.x) - map_x) * delta_x;
		}
		if (ray_dir_x > 0)
		{
			step_x = 1;
			side_x = (map_x + 1.0 - (d->ply.pos.x)) * delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_y = ((d->ply.pos.y) - map_y) * delta_y;
		}
		if (ray_dir_y > 0)
		{
			step_y = 1;
			side_y = (map_y + 1.0 - (d->ply.pos.y)) * delta_y;
		}
		while (hit == 0)
		{
			if (side_x < side_y)
			{
				side_x += delta_x;
				map_x += step_x;
				wall_side = 0;
			}
			if (side_y < side_x)
			{
				side_y += delta_y;
				map_y += step_y;
				wall_side = 1;
			}
			if (d->map[map_y][map_x] != '0')
				hit = 1;
			mlx_image_to_window(d->mlx, d->im.mini_p, map_x * TILE, map_y
				* TILE);
		}
	}
}
