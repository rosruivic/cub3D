#include "../includes/cub3D.h"

static void	ft_draw(t_data *d, int x, int draw_start, int draw_end)
{
	int	i;

	i = draw_start;
	while (i < draw_end)
	{
		mlx_put_pixel(d->im.background, x, i, 0xFF0000FF);
		i++;
	}
}

void	ft_raycasting(t_data *d)
{
	int		i;
	double	pos_x;
	int		map_x;
	double	pos_y;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	step_x;
	double	step_y;
	int		hit;
	int		wall_side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;

	wall_side = 0;
	hit = 0;
	step_x = 0;
	step_y = 0;
	i = -1;
	pos_x = d->ply.pos.x + 0.5;
	pos_y = d->ply.pos.y + 0.5;
	// dir_x = d->ply.dir.x;
	// dir_y = d->ply.dir.y;
	// plane_x = d->ply.cam.x;
	// plane_y = d->ply.cam.y;
	// if (dir_x == -1 && dir_y == 0)
	// {
	// 	plane_x = 0;
	// 	plane_y = 0.66;
	// }
	// if (dir_x == 1 && dir_y == 0)
	// {
	// 	plane_x = 0;
	// 	plane_y = -0.66;
	// }
	// if (dir_y == -1 && dir_x == 0)
	// {
	// 	plane_x = -0.66;
	// 	plane_y = 0;
	// }
	// if (dir_y == 1 && dir_x == 0)
	// {
	// 	plane_x = 0.66;
	// 	plane_y = 0;
	// }
	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	printf("pos:%f,%f, dir:%f,%f, plane:%f,%f\n", pos_x, pos_y, dir_x, dir_y,
			plane_x, plane_y);
	while (++i < W)
	{
		cam_x = 2 * i / (double)W - 1;
		ray_dir_x = dir_x + plane_x * cam_x;
		ray_dir_y = dir_y + plane_y * cam_x;
		map_x = (int)pos_x;
		map_y = (int)pos_y;
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
			side_x = (pos_x - map_x) * delta_x;
		}
		else
		{
			step_x = 1;
			side_x = (map_x + 1.0 - pos_x) * delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_y = (pos_y - map_y) * delta_y;
		}
		else
		{
			step_y = 1;
			side_x = (map_y + 1.0 - pos_y) * delta_y;
		}
		while (hit == 0)
		{
			if (side_x < side_y)
			{
				side_x += delta_x;
				map_x += step_x;
				wall_side = 0;
			}
			else
			{
				side_y += delta_y;
				map_y += step_y;
				wall_side = 1;
			}
			if (d->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (wall_side == 0)
			perp_wall_dist = side_x - delta_x;
		else
			perp_wall_dist = side_y - delta_y;
		line_height = (int)(H / perp_wall_dist);
		draw_start = -line_height / 2 + H / 2;
		if (draw_start >= H)
			draw_start = H - 1;
		draw_end = line_height / 2 + H / 2;
		if (draw_end < 0)
			draw_end = 0;
		printf("draw_start: %d, draw_end: %d\n", draw_start, draw_end);
		ft_draw(d, i, draw_end, draw_start);
	}
}
