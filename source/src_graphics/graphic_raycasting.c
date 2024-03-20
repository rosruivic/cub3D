#include "../includes/cub3D.h"

uint32_t	ft_get_uin32(uint8_t *conv, int n)
{
	uint32_t	u;

	u = conv[n] << 24;
	u += conv[n + 1] << 16;
	u += conv[n + 2] << 8;
	u += conv[n + 3];
	return (u);
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
	double	step;
	double	tex_pos;
	int		j;
	int		color;

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
			tex_x = TEXW - tex_x - 1;
		if (wall_side == 1 && ray_dir_x < 0)
			tex_x = TEXW - tex_x - 1;
		step = 1.0 * TEXH / line_height;
		tex_pos = (draw_start - H / 2 + line_height / 2) * step;
		j = draw_start;
		while (j < draw_end)
		{
			tex_pos += step;
			if (wall_side == 0 && map_x < (int)d->ply.pos.x)
				color = ft_get_uin32(d->tex.we->pixels, d->tex.we->width
						* (int)tex_pos * 4 + (int)tex_x * 4);
			else if (wall_side == 0 && map_x > (int)d->ply.pos.x)
				color = ft_get_uin32(d->tex.ea->pixels, d->tex.ea->width
						* (int)tex_pos * 4 + (int)tex_x * 4);
			else if (wall_side == 1 && map_y < (int)d->ply.pos.y)
				color = ft_get_uin32(d->tex.no->pixels, d->tex.no->width
						* (int)tex_pos * 4 + (int)tex_x * 4);
			else if (wall_side == 1 && map_y > (int)d->ply.pos.y)
				color = ft_get_uin32(d->tex.so->pixels, d->tex.so->width
						* (int)tex_pos * 4 + (int)tex_x * 4);
			mlx_put_pixel(d->im.background, i, j, color);
			j++;
		}
	}
}
