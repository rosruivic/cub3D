//#include "../includes/cub3D.h"
//#include "includes/cub3D.h"
#include "cub3D.h"

static void	ft_cub_flood_fill(int x, int y, t_data *d)
{ // las coord son respecto a la player_pos en la sandbox
	d->sandbox[y][x] = '.';

	if (d->sandbox[y - 1][x] == 'X' || d->sandbox[y + 1][x] == 'X'
		|| d->sandbox[y][x - 1] == 'X' || d->sandbox[y][x + 1] == 'X'
		|| d->sandbox[y - 1][x] == ' ' || d->sandbox[y + 1][x] == ' '
		|| d->sandbox[y][x - 1] == ' ' || d->sandbox[y][x + 1] == ' ')
			ft_error_map_data(d, ERROR_MAP_NO_CLOSED_WALLS);
	if (d->sandbox[y - 1][x] != '1' && d->sandbox[y - 1][x] != '.')
		ft_cub_flood_fill(x, y - 1, d);
	if (d->sandbox[y + 1][x] != '1' && d->sandbox[y + 1][x] != '.')
		ft_cub_flood_fill(x, y + 1, d);
	if (d->sandbox[y][x - 1] != '1' && d->sandbox[y][x - 1] != '.')
		ft_cub_flood_fill(x - 1, y, d);
	if (d->sandbox[y][x + 1] != '1' && d->sandbox[y][x + 1] != '.')
		ft_cub_flood_fill(x + 1, y, d);
}

static int	ft_longer_row(t_data *d)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (++i < ft_matrix_len(d->map))
	{
		if (len < (int)ft_strlen(d->map[i]))
			len = (int)ft_strlen(d->map[i]);
	}
	return (len);
}

static void	ft_build_sandbox_first_line(t_data *d)
{
	int	j;

	d->sandbox[0] = malloc((ft_longer_row(d) + 2 + 1) * sizeof(char));
	if (!d->sandbox[0])
		ft_error_map_data(d, ERROR_MALLOC);
	j = -1;
	while (++j < ft_longer_row(d) + 2)
		d->sandbox[0][j] = 'X';
	d->sandbox[0][j] = '\0';
	ft_printf("%s\n", d->sandbox[0]);
}

static int	ft_build_sandbox_inter_lines(t_data *d, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (++i < rows - 2)
	{
		j = 0;
		d->sandbox[i] = malloc((ft_longer_row(d) + 2) * sizeof(char));
		if (!d->sandbox[i])
			ft_error_map_data(d, ERROR_MALLOC);
		d->sandbox[i][0] = 'X';
		while (++j < (int)ft_strlen(d->map[i - 1]) + 1)
			d->sandbox[i][j] = d->map[i - 1][j - 1];
		d->sandbox[i][j] = 'X';
		while (++j < ft_longer_row(d) + 2)
			d->sandbox[i][j] = 'X';
		d->sandbox[i][j] = '\0';
		ft_printf("%s\n", d->sandbox[i]);
	}
	return (i);
}

static void	ft_build_sandbox_last_line(t_data *d, int i)
{
	int	j;

	d->sandbox[i] = malloc((ft_longer_row(d) + 2) * sizeof(char));
	if (!d->sandbox[i])
		ft_error_map_data(d, ERROR_MALLOC);
	j = -1;
	while (++j < ft_longer_row(d) + 2)
		d->sandbox[i][j] = 'X';
	d->sandbox[i][j] = '\0';
}

static void	ft_build_sandbox(t_data *d)
{
	int	rows;
	int i;

	rows = ft_matrix_len(d->map) + 2 + 1;
	d->sandbox = ft_calloc(rows + 1, sizeof(char *));
	if (!d->sandbox)
		ft_error_map_data(d, ERROR_MALLOC);
	ft_build_sandbox_first_line(d);
	i = ft_build_sandbox_inter_lines(d, rows);
	ft_build_sandbox_last_line(d, i);
	ft_printf("%s\n", d->sandbox[i]);
	ft_printf("\n");
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
	ft_cub_flood_fill(d->pos.x + 1, d->pos.y + 1, d);
	ft_print_matrix(d->sandbox);
	d->sandbox = ft_freedom_null(d->sandbox);
}
