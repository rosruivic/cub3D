/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:23:23 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/03/22 18:23:24 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_w(t_data *d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
	{
		if (d->map[(int)(d->ply.pos.y + d->move_speed
				* d->ply.dir.y)][(int)(d->ply.pos.x + d->move_speed
				* d->ply.dir.x)] != '1' && d->map[(int)(d->ply.pos.y
				+ d->move_speed * d->ply.dir.y)][(int)(d->ply.pos.x
				+ d->move_speed * d->ply.dir.x)] != ' '
			&& d->map[(int)(d->ply.pos.y + d->move_speed
				* d->ply.dir.y)][(int)(d->ply.pos.x + d->move_speed
				* d->ply.dir.x)] != '\0')
		{
			d->ply.pos.y += d->move_speed * d->ply.dir.y;
			d->ply.pos.x += d->move_speed * d->ply.dir.x;
			ft_background(d);
			ft_raycasting(d);
			ft_move_minimap(d);
		}
	}
}

void	ft_s(t_data *d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
	{
		if (d->map[(int)(d->ply.pos.y - d->move_speed
				* d->ply.dir.y)][(int)(d->ply.pos.x - d->move_speed
				* d->ply.dir.x)] != '1' && d->map[(int)(d->ply.pos.y
				- d->move_speed * d->ply.dir.y)][(int)(d->ply.pos.x
				- d->move_speed * d->ply.dir.x)] != ' '
			&& d->map[(int)(d->ply.pos.y - d->move_speed
				* d->ply.dir.y)][(int)(d->ply.pos.x - d->move_speed
				* d->ply.dir.x)] != '\0')
		{
			d->ply.pos.y -= d->move_speed * d->ply.dir.y;
			d->ply.pos.x -= d->move_speed * d->ply.dir.x;
			ft_background(d);
			ft_raycasting(d);
			ft_move_minimap(d);
		}
	}
}

void	ft_d(t_data *d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
	{
		if (d->map[(int)(d->ply.pos.y + d->move_speed
				* d->ply.cam.y)][(int)(d->ply.pos.x + d->move_speed
				* d->ply.cam.x)] != '1' && d->map[(int)(d->ply.pos.y
				+ d->move_speed * d->ply.cam.y)][(int)(d->ply.pos.x
				+ d->move_speed * d->ply.cam.x)] != ' '
			&& d->map[(int)(d->ply.pos.y + d->move_speed
				* d->ply.cam.y)][(int)(d->ply.pos.x + d->move_speed
				* d->ply.cam.x)] != '\0')
		{
			d->ply.pos.y += d->move_speed * d->ply.cam.y;
			d->ply.pos.x += d->move_speed * d->ply.cam.x;
			ft_background(d);
			ft_raycasting(d);
			ft_move_minimap(d);
		}
	}
}

void	ft_a(t_data *d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
	{
		if (d->map[(int)(d->ply.pos.y - d->move_speed
				* d->ply.cam.y)][(int)(d->ply.pos.x - d->move_speed
				* d->ply.cam.x)] != '1' && d->map[(int)(d->ply.pos.y
				- d->move_speed * d->ply.cam.y)][(int)(d->ply.pos.x
				- d->move_speed * d->ply.cam.x)] != ' '
			&& d->map[(int)(d->ply.pos.y - d->move_speed
				* d->ply.cam.y)][(int)(d->ply.pos.x - d->move_speed
				* d->ply.cam.x)] != '\0')
		{
			d->ply.pos.y -= d->move_speed * d->ply.cam.y;
			d->ply.pos.x -= d->move_speed * d->ply.cam.x;
			ft_background(d);
			ft_raycasting(d);
			ft_move_minimap(d);
		}
	}
}
