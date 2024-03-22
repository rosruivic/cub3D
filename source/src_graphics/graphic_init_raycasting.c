/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init_raycasting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:23:15 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/03/22 18:23:16 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_init_raycasting(t_data *d)
{
	d->g.step_move.x = 0;
	d->g.step_move.y = 0;
}

void	ft_init_boucle_raycasting(t_data *d, int i)
{
	d->g.hit = 0;
	d->g.cam_x = 2 * i / (double)W - 1;
	d->g.ray_dir.x = d->ply.dir.x + d->ply.cam.x * d->g.cam_x;
	d->g.ray_dir.y = d->ply.dir.y + d->ply.cam.y * d->g.cam_x;
	d->g.map.x = (int)d->ply.pos.x;
	d->g.map.y = (int)d->ply.pos.y;
	if (d->g.ray_dir.x != 0)
		d->g.delta.x = fabs(1 / d->g.ray_dir.x);
	else
		d->g.delta.x = 1e30;
	if (d->g.ray_dir.y != 0)
		d->g.delta.y = fabs(1 / d->g.ray_dir.y);
	else
		d->g.delta.y = 1e30;
}

void	ft_second_init_boucle_raycasting(t_data *d)
{
	if (d->g.ray_dir.x < 0)
	{
		d->g.step_move.x = -1;
		d->g.side.x = ((d->ply.pos.x) - d->g.map.x) * d->g.delta.x;
	}
	else
	{
		d->g.step_move.x = 1;
		d->g.side.x = (d->g.map.x + 1.0 - (d->ply.pos.x)) * d->g.delta.x;
	}
	if (d->g.ray_dir.y < 0)
	{
		d->g.step_move.y = -1;
		d->g.side.y = ((d->ply.pos.y) - d->g.map.y) * d->g.delta.y;
	}
	else
	{
		d->g.step_move.y = 1;
		d->g.side.y = (d->g.map.y + 1.0 - (d->ply.pos.y)) * d->g.delta.y;
	}
}
