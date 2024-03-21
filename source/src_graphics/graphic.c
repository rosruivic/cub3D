#include "../includes/cub3D.h"

void	ft_background(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < H)
	{
		j = -1;
		while (++j < H)
		{
			if (j < H / 2)
				mlx_put_pixel(d->im.background, i, j, d->hex_c);
			else
				mlx_put_pixel(d->im.background, i, j, d->hex_f);
		}
	}
}
// if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		mlx_close_window(game->mlx);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_W) && ft_valid_move(game,
// 			(game->player->instances[0].y / PIX) - 1,
// 			game->player->instances[0].x / PIX))
// 		game->player->instances[0].y -= 64;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_S) && ft_valid_move(game,
// 			(game->player->instances[0].y / PIX) + 1,
// 			game->player->instances[0].x / PIX))
// 		game->player->instances[0].y += 64;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_A) && ft_valid_move(game,
// 			game->player->instances[0].y / PIX, (game->player->instances[0].x
// 				/ PIX - 1)))
// 		game->player->instances[0].x -= 64;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_D) && ft_valid_move(game,
// 			game->player->instances[0].y / PIX, (game->player->instances[0].x
// 				/ PIX + 1)))
// 		game->player->instances[0].x += 64;
// A, S, D, W player movement
// <-, -> view movement

void	ft_right(t_data *d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
	{
		d->old_dir = d->ply.dir.x;
		d->ply.dir.x = d->ply.dir.x * cos(d->rot_speed) - d->ply.dir.y
			* sin(d->rot_speed);
		d->ply.dir.y = d->old_dir * sin(d->rot_speed) + d->ply.dir.y
			* cos(d->rot_speed);
		d->old_plane = d->ply.cam.x;
		d->ply.cam.x = d->ply.cam.x * cos(d->rot_speed) - d->ply.cam.y
			* sin(d->rot_speed);
		d->ply.cam.y = d->old_plane * sin(d->rot_speed) + d->ply.cam.y
			* cos(d->rot_speed);
		ft_background(d);
		ft_raycasting(d);
		ft_move_minimap(d);
	}
}

void	ft_left(t_data *d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
	{
		d->old_dir = d->ply.dir.x;
		d->ply.dir.x = d->ply.dir.x * cos(-d->rot_speed) - d->ply.dir.y
			* sin(-d->rot_speed);
		d->ply.dir.y = d->old_dir * sin(-d->rot_speed) + d->ply.dir.y
			* cos(-d->rot_speed);
		d->old_plane = d->ply.cam.x;
		d->ply.cam.x = d->ply.cam.x * cos(-d->rot_speed) - d->ply.cam.y
			* sin(-d->rot_speed);
		d->ply.cam.y = d->old_plane * sin(-d->rot_speed) + d->ply.cam.y
			* cos(-d->rot_speed);
		ft_background(d);
		ft_raycasting(d);
		ft_move_minimap(d);
	}
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;

	d = param;
	d->move_speed = 5.0 * d->mlx->delta_time;
	d->rot_speed = 3.0 * d->mlx->delta_time;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(d->mlx);
	ft_w(d, keydata);
	ft_s(d, keydata);
	ft_d(d, keydata);
	ft_a(d, keydata);
	ft_right(d, keydata);
	ft_left(d, keydata);
}

void	ft_graphic(t_data *d)
{
	d->mlx = mlx_init(H, W, "Cubilete", false);
	d->im.background = mlx_new_image(d->mlx, W, H);
	mlx_image_to_window(d->mlx, d->im.background, 0, 0);
	ft_background(d);
	ft_minimap(d);
	ft_raycasting(d);
	mlx_key_hook(d->mlx, &ft_keyhook, d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
}
