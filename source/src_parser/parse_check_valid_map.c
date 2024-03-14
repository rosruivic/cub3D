#include "cub3D.h"

static void	ft_fill_player_dir(t_data *d, int x, int y)
{
	d->ply.dir.x = x;
	d->ply.dir.y = y;
	if (d->ply.dir.x == -1 && d->ply.dir.y == 0)
	{
		d->ply.cam.x = 0;
		d->ply.cam.y = 0.66;
	}
	if (d->ply.dir.x == 1 && d->ply.dir.y == 0)
	{
		d->ply.cam.x = 0;
		d->ply.cam.y = -0.66;
	}
	if (d->ply.dir.y == -1 && d->ply.dir.x == 0)
	{
		d->ply.cam.x = -0.66;
		d->ply.cam.y = 0;
	}
	if (d->ply.dir.y == 1 && d->ply.dir.x == 0)
	{
		d->ply.cam.x = 0.66;
		d->ply.cam.y = 0;
	}
}

static void	ft_check_player(t_data *d, int i, int j)
{
	if (d->map[i][j] == 'N' || d->map[i][j] == 'S' || d->map[i][j] == 'W'
		|| d->map[i][j] == 'E')
	{
		if (d->ply.pos.x < 0)
		{
			d->ply.pos.x = j + 0.5;
			d->ply.pos.y = i + 0.5;
			if (d->map[i][j] == 'N')
				ft_fill_player_dir(d, 0, -1);
			else if (d->map[i][j] == 'S')
				ft_fill_player_dir(d, 0, 1);
			else if (d->map[i][j] == 'W')
				ft_fill_player_dir(d, -1, 0);
			else if (d->map[i][j] == 'E')
				ft_fill_player_dir(d, 1, 0);
		}
		else
			ft_error_map_data(d, ERROR_MAP_DUPLICATE_PLAYER);
	}
}

/**
 * @brief 
 * At the 2nd while:
 * // I don't know why 'j' don't catch more than 14 chars:
 * 	while (d->map[++j] != NULL) 
 * @param d 
 */
static void	ft_check_chars_and_player(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (d->map[++i])
	{
		while (++j < (int)ft_strlen(d->map[i]))
		{
			if (d->map[i][j] != '1' && d->map[i][j] != '0'
				&& d->map[i][j] != 'N' && d->map[i][j] != 'S'
				&& d->map[i][j] != 'W' && d->map[i][j] != 'E'
				&& d->map[i][j] != ' ')
				ft_error_map_data(d, ERROR_MAP_FORBIDDEN_CHAR);
			ft_check_player(d, i, j);
		}
		j = -1;
	}
	if (d->ply.pos.x < 0)
		ft_error_map_data(d, ERROR_MAP_NO_PLAYER);
}

void	ft_check_valid_map(t_data *d)
{
	ft_check_chars_and_player(d);
	ft_check_closed_walls(d);
}
