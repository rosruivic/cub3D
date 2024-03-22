/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:23:27 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/03/22 18:23:28 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// void	ft_init_raycasting(t_data *d)
// {
// 	d->g.step_move.x = 0;
// 	d->g.step_move.y = 0;
// }

// void	ft_init_boucle_raycasting(t_data *d, int i)
// {
// 	d->g.hit = 0;
// 	d->g.cam_x = 2 * i / (double)W - 1;
// 	d->g.ray_dir.x = d->ply.dir.x + d->ply.cam.x * d->g.cam_x;
// 	d->g.ray_dir.y = d->ply.dir.y + d->ply.cam.y * d->g.cam_x;
// 	d->g.map.x = (int)d->ply.pos.x;
// 	d->g.map.y = (int)d->ply.pos.y;
// 	if (d->g.ray_dir.x != 0)
// 		d->g.delta.x = fabs(1 / d->g.ray_dir.x);
// 	else
// 		d->g.delta.x = 1e30;
// 	if (d->g.ray_dir.y != 0)
// 		d->g.delta.y = fabs(1 / d->g.ray_dir.y);
// 	else
// 		d->g.delta.y = 1e30;
// }

// void	ft_second_init_boucle_raycasting(t_data *d)
// {
// 	if (d->g.ray_dir.x < 0)
// 	{
// 		d->g.step_move.x = -1;
// 		d->g.side.x = ((d->ply.pos.x) - d->g.map.x) * d->g.delta.x;
// 	}
// 	else
// 	{
// 		d->g.step_move.x = 1;
// 		d->g.side.x = (d->g.map.x + 1.0 - (d->ply.pos.x)) * d->g.delta.x;
// 	}
// 	if (d->g.ray_dir.y < 0)
// 	{
// 		d->g.step_move.y = -1;
// 		d->g.side.y = ((d->ply.pos.y) - d->g.map.y) * d->g.delta.y;
// 	}
// 	else
// 	{
// 		d->g.step_move.y = 1;
// 		d->g.side.y = (d->g.map.y + 1.0 - (d->ply.pos.y)) * d->g.delta.y;
// 	}
// }

void	ft_hit_wall(t_data *d)
{
	while (d->g.hit == 0)
	{
		if (d->g.side.x < d->g.side.y)
		{
			d->g.side.x += d->g.delta.x;
			d->g.map.x += d->g.step_move.x;
			d->g.wall_side = 0;
		}
		else if (d->g.side.y < d->g.side.x)
		{
			d->g.side.y += d->g.delta.y;
			d->g.map.y += d->g.step_move.y;
			d->g.wall_side = 1;
		}
		if (d->map[d->g.map.y][d->g.map.x] != '0'
			&& d->map[d->g.map.y][d->g.map.x] != 'W'
			&& d->map[d->g.map.y][d->g.map.x] != 'E'
			&& d->map[d->g.map.y][d->g.map.x] != 'N'
			&& d->map[d->g.map.y][d->g.map.x] != 'S')
			d->g.hit = 1;
	}
}

void	ft_principal_boucle(t_data *d)
{
	if (d->g.wall_side == 0)
		d->g.perp_wall_dist = d->g.side.x - d->g.delta.x;
	else
		d->g.perp_wall_dist = d->g.side.y - d->g.delta.y;
	d->g.line_height = (int)(H / d->g.perp_wall_dist);
	d->g.draw.x = -d->g.line_height / 2 + H / 2;
	if (d->g.draw.x < 0)
		d->g.draw.x = 0;
	d->g.draw.y = d->g.line_height / 2 + H / 2;
	if (d->g.draw.y >= H)
		d->g.draw.y = H - 1;
	if (d->g.wall_side == 0)
		d->g.wall_x = d->ply.pos.y + d->g.perp_wall_dist * d->g.ray_dir.y;
	else
		d->g.wall_x = d->ply.pos.x + d->g.perp_wall_dist * d->g.ray_dir.x;
	d->g.wall_x -= floor(d->g.wall_x);
	d->g.tex_x = (int)(d->g.wall_x * (double)d->tex.no->width);
	if (d->g.wall_side == 0 && d->g.map.x < (int)d->ply.pos.x)
		d->g.tex_x = TEXW - d->g.tex_x - 1;
	if (d->g.wall_side == 1 && d->g.map.y > (int)d->ply.pos.y)
		d->g.tex_x = TEXW - d->g.tex_x - 1;
	d->g.step = 1.0 * TEXH / d->g.line_height;
	d->g.tex_pos = (d->g.draw.x - H / 2 + d->g.line_height / 2) * d->g.step;
}

void	ft_color_wall(t_data *d, int i)
{
	int	j;

	j = d->g.draw.x;
	while (j < d->g.draw.y)
	{
		if (d->g.wall_side == 0 && d->g.map.x < (int)d->ply.pos.x)
			d->g.color = ft_get_uin32(d->tex.we->pixels,
					d->tex.we->width * (int)d->g.tex_pos * 4
					+ (int)d->g.tex_x * 4);
		else if (d->g.wall_side == 0 && d->g.map.x > (int)d->ply.pos.x)
			d->g.color = ft_get_uin32(d->tex.ea->pixels,
					d->tex.ea->width * (int)d->g.tex_pos * 4
					+ (int)d->g.tex_x * 4);
		else if (d->g.wall_side == 1 && d->g.map.y < (int)d->ply.pos.y)
			d->g.color = ft_get_uin32(d->tex.no->pixels,
					d->tex.no->width * (int)d->g.tex_pos * 4
					+ (int)d->g.tex_x * 4);
		else if (d->g.wall_side == 1 && d->g.map.y > (int)d->ply.pos.y)
			d->g.color = ft_get_uin32(d->tex.so->pixels,
					d->tex.so->width * (int)d->g.tex_pos * 4
					+ (int)d->g.tex_x * 4);
		mlx_put_pixel(d->im.background, i, j, d->g.color);
		d->g.tex_pos += d->g.step;
		j++;
	}
}

void	ft_raycasting(t_data *d)
{
	int	i;

	ft_init_raycasting(d);
	i = -1;
	while (++i < W)
	{
		ft_init_boucle_raycasting(d, i);
		ft_second_init_boucle_raycasting(d);
		ft_hit_wall(d);
		ft_principal_boucle(d);
		ft_color_wall(d, i);
	}
}
