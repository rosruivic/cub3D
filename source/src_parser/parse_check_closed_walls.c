#include "cub3D.h"

static void	ft_cub_flood_fill(int x, int y, t_data *d)
{
	d->box[y][x] = '.';
	if (d->box[y - 1][x] == 'X' || d->box[y + 1][x] == 'X'
		|| d->box[y][x - 1] == 'X' || d->box[y][x + 1] == 'X'
		|| d->box[y - 1][x] == ' ' || d->box[y + 1][x] == ' '
		|| d->box[y][x - 1] == ' ' || d->box[y][x + 1] == ' ')
		ft_error_map_data(d, ERROR_MAP_NO_CLOSED_WALLS);
	if (d->box[y - 1][x] != '1' && d->box[y - 1][x] != '.')
		ft_cub_flood_fill(x, y - 1, d);
	if (d->box[y + 1][x] != '1' && d->box[y + 1][x] != '.')
		ft_cub_flood_fill(x, y + 1, d);
	if (d->box[y][x - 1] != '1' && d->box[y][x - 1] != '.')
		ft_cub_flood_fill(x - 1, y, d);
	if (d->box[y][x + 1] != '1' && d->box[y][x + 1] != '.')
		ft_cub_flood_fill(x + 1, y, d);
}

static void	ft_locate_zeroes(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	while (d->box[++i])
	{
		j = -1;
		while (d->box[i][++j])
		{
			if (d->box[i][j] == '0')
				ft_cub_flood_fill(j, i, d);
		}
	}
}

/**
 * @brief 
 * 	
	// IDEA: EL MAPA GEMELO DEBERÍA TENER UN MURO EXTERNO DE CONTENCIÓN
	// o sea, que cuando creo el mapa gemelo, la matriz la hago de
	// unas dimensiones tales que:
	//  - (+2) filas que el mapa original
	//  - (+2) columnas que la fila más larga
	//  - relleno primera y última fila con 'X'
	//  - relleno primera y última columna con 'X'
	// después, si flood-fill llega hasta alguna X (no cambiar y error)
 * @param d 
 */
void	ft_check_closed_walls(t_data *d)
{
	ft_build_sandbox(d);
	ft_cub_flood_fill(d->ply.pos.x + 1, d->ply.pos.y + 1, d);
	ft_locate_zeroes(d);
	d->box = ft_freedom_null(d->box);
}
