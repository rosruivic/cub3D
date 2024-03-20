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
	int		map_x;
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
	double	wall_x;
	int		tex_x;

	wall_side = 0;
	step_x = 0;
	step_y = 0;
	i = -1;
	dir_x = d->ply.dir.x;
	dir_y = d->ply.dir.y;
	plane_x = d->ply.cam.x;
	plane_y = d->ply.cam.y;
	while (++i < W)
	{
		hit = 0;
		cam_x = 2 * i / (double)W - 1;
		ray_dir_x = dir_x + plane_x * cam_x;
		ray_dir_y = dir_y + plane_y * cam_x;
		map_x = (int)d->ply.pos.x;
		map_y = (int)d->ply.pos.y;
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
		else
		{
			step_x = 1;
			side_x = (map_x + 1.0 - (d->ply.pos.x)) * delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_y = ((d->ply.pos.y) - map_y) * delta_y;
		}
		else
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
			else if (side_y < side_x)
			{
				side_y += delta_y;
				map_y += step_y;
				wall_side = 1;
			}
			if (d->map[map_y][map_x] != '0' && d->map[map_y][map_x] != 'W'
				&& d->map[map_y][map_x] != 'E' && d->map[map_y][map_x] != 'N'
				&& d->map[map_y][map_x] != 'S')
				hit = 1;
		}
		if (wall_side == 0)
			perp_wall_dist = side_x - delta_x;
		else
			perp_wall_dist = side_y - delta_y;
		line_height = (int)(H / perp_wall_dist);
		draw_start = -line_height / 2 + H / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + H / 2;
		if (draw_end >= H)
			draw_end = H - 1;
		if (wall_side == 0)
			wall_x = d->ply.pos.y + perp_wall_dist * ray_dir_y;
		else
			wall_x = d->ply.pos.x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * (double)d->tex.no->width);
		if (wall_side == 0 && ray_dir_x > 0)
			tex_x = d->tex.no->width - tex_x - 1;
		if (wall_side == 1 && ray_dir_x < 0)
			tex_x = d->tex.no->width - tex_x - 1;
		ft_draw(d, i, draw_start, draw_end);
	}
}
