#include "../includes/cub3D.h"

static void	ft_background(t_data *d)
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
void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;
	double	old_dir_x;
	double	old_plane_x;

	d = param;
	(void)d;
	(void)keydata;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(d->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
	{
		d->ply.pos.y += MOVE_SPEED * d->ply.dir.y;
		d->ply.pos.x += MOVE_SPEED * d->ply.dir.x;
		ft_background(d);
		ft_raycasting(d);
		printf("pos_X:%f, pos_Y:%f\n", d->ply.pos.x, d->ply.pos.y);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
	{
		d->ply.pos.y -= MOVE_SPEED * d->ply.dir.y;
		d->ply.pos.x -= MOVE_SPEED * d->ply.dir.x;
		ft_background(d);
		ft_raycasting(d);
		printf("pos_X:%f, pos_Y:%f\n", d->ply.pos.x, d->ply.pos.y);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
	{
		d->ply.pos.y += MOVE_SPEED * d->ply.cam.y;
		d->ply.pos.x += MOVE_SPEED * d->ply.cam.x;
		ft_background(d);
		ft_raycasting(d);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
	{
		d->ply.pos.y -= MOVE_SPEED * d->ply.cam.y;
		d->ply.pos.x -= MOVE_SPEED * d->ply.cam.x;
		ft_background(d);
		ft_raycasting(d);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
	{
		old_dir_x = d->ply.dir.x;
		d->ply.dir.x = d->ply.dir.x * cos(ROTATE_SPEED) - d->ply.dir.y * sin(ROTATE_SPEED);
		d->ply.dir.y = old_dir_x * sin(ROTATE_SPEED) + d->ply.dir.y * cos(ROTATE_SPEED);
		old_plane_x = d->ply.cam.x;
		d->ply.cam.x = d->ply.cam.x * cos(ROTATE_SPEED) - d->ply.cam.y * sin(ROTATE_SPEED);
		d->ply.cam.y = old_plane_x * sin(ROTATE_SPEED) + d->ply.cam.y * cos(ROTATE_SPEED);
		ft_background(d);
		ft_raycasting(d);
		printf("Izquierda\n");
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
	{
		old_dir_x = d->ply.dir.x;
		d->ply.dir.x = d->ply.dir.x * cos(-ROTATE_SPEED) - d->ply.dir.y * sin(-ROTATE_SPEED);
		d->ply.dir.y = old_dir_x * sin(-ROTATE_SPEED) + d->ply.dir.y * cos(-ROTATE_SPEED);
		old_plane_x = d->ply.cam.x;
		d->ply.cam.x = d->ply.cam.x * cos(-ROTATE_SPEED) - d->ply.cam.y * sin(-ROTATE_SPEED);
		d->ply.cam.y = old_plane_x * sin(-ROTATE_SPEED) + d->ply.cam.y * cos(-ROTATE_SPEED);
		ft_background(d);
		ft_raycasting(d);
		printf("Derecha\n");
	}
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
