/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_calc_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:23:12 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/03/22 18:23:13 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_hit_wall_minimap(t_data *d)
{
	while (d->g.hit == 0)
	{
		if (d->g.side.x < d->g.side.y)
		{
			d->g.side.x += d->g.delta.x;
			d->g.map.x += d->g.step_move.x;
			d->g.wall_side = 0;
		}
		if (d->g.side.y < d->g.side.x)
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
		else
			mlx_image_to_window(d->mlx, d->im.mini_r, d->g.map.x * TILE,
				d->g.map.y * TILE);
	}
}

void	ft_calc_vector(t_data *d)
{
	int	i;

	ft_init_raycasting(d);
	i = -1;
	while (++i < W)
	{
		ft_init_boucle_raycasting(d, i);
		ft_second_init_boucle_raycasting(d);
		ft_hit_wall_minimap(d);
	}
}
