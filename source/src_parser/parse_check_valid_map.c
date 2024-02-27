#include "cub3D.h"

static void	ft_check_player(t_data *d, int i, int j)
{
	if (d->map[i][j] == 'N' || d->map[i][j] == 'S'
		|| d->map[i][j] == 'W' || d->map[i][j] == 'E')
	{
		if (d->pos.d == NONE)
		{
			d->pos.x = j;
			d->pos.y = i;
			if (d->map[i][j] == 'N')
				d->pos.d = N;
			else if (d->map[i][j] == 'S')
				d->pos.d = S;
			else if (d->map[i][j] == 'W')
				d->pos.d = W;
			else if (d->map[i][j] == 'E')
				d->pos.d = E;
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
	if (d->pos.d == NONE)
		ft_error_map_data(d, ERROR_MAP_NO_PLAYER);
}

void	ft_check_valid_map(t_data *d)
{
	ft_check_chars_and_player(d);
	ft_check_closed_walls(d);
}
