//#include "../includes/cub3D.h"
#include "includes/cub3D.h"

/* static void	ft_print_map(char **map)
{
	if (map)
	{
		int i = -1;
		ft_printf("\n");
		while(map[++i])
			ft_printf("%s\n", map[i]);
		ft_printf("\n");
	}
} */

/* static void	ft_cub_flood_fill(int x, int y, t_data *d)
{ // las coord son respecto a la player_pos en la sandbox, calcularlas
	d->sandbox[y][x] = '.';

	if (d->sandbox[y - 1][x] == 'X' || d->sandbox[y + 1][x] == 'X'
		|| d->sandbox[y][x - 1] != 'X' || d->sandbox[y][x + 1] != 'X')
			ft_error_map_data(d, ERROR_MAP_NO_CLOSED_WALLS);
	if (d->sandbox[y - 1][x] != '1' && d->sandbox[y - 1][x] != '.')
		ft_cub_flood_fill(x, y - 1, d);
	if (d->sandbox[y + 1][x] != '1' && d->sandbox[y + 1][x] != '.')
		ft_cub_flood_fill(x, y + 1, d);
	if (d->sandbox[y][x - 1] != '1' && d->sandbox[y][x - 1] != '.')
		ft_cub_flood_fill(x - 1, y, d);
	if (d->sandbox[y][x + 1] != '1' && d->sandbox[y][x + 1] != '.')
		ft_cub_flood_fill(x + 1, y, d);
} */

/* static void	ft_built_sandbox(t_data *d)
{
	int	i;

	i = -1;
	d->sandbox = ft_calloc(ft_matrix_len(d->map) + 1, sizeof(char *));
	if (!d->sandbox)
		ft_error_map_data(d, ERROR_MALLOC);
	while (++i < ft_matrix_len(d->map))
	{
		d->sandbox[i] = ft_strdup(d->map[i]);
		if (!d->sandbox[i])
		{
			d->sandbox = ft_freedom(d->sandbox);
			ft_error_map_data(d, ERROR_MALLOC);
		}
		ft_printf("%s\n", d->sandbox[i]);
	}
	ft_print_map(d->sandbox);
} */

/**
 * @brief
 * 	Una vez determinadas sus dimensiones, hay que pasar los contenidos
 *  artesanalmente, uno a uno, carácter a carácter (no vale strdup)
 * 
 * @param d 
 */
static void	ft_build_sandbox(t_data *d)
{
	int	rows;
	int i;
	int	j;

	i = 0;
	rows = ft_matrix_len(d->map) + 2 + 1;
	d->sandbox = ft_calloc(rows + 1, sizeof(char *));
	if (!d->sandbox)
		ft_error_map_data(d, ERROR_MALLOC);
// primera fila:
	d->sandbox[0] = malloc(((int)ft_strlen(d->map[0]) + 2) * sizeof(char));
	if (!d->sandbox[0])
		ft_error_map_data(d, ERROR_MALLOC);
	j = -1;
	while (++j < (int)ft_strlen(d->map[0]) + 2)
		d->sandbox[0][j] = 'X';
	d->sandbox[0][j] = '\0';
	ft_printf("%s\n", d->sandbox[0]);

// filas intermedias:
	while (++i < rows - 1)
	{
		j = 0;
		d->sandbox[i] = malloc(((int)ft_strlen(d->map[i - 1]) + 2) * sizeof(char));
		if (!d->sandbox[i])
			ft_error_map_data(d, ERROR_MALLOC);
		d->sandbox[i][0] = 'X';
		while (++j < (int)ft_strlen(d->map[i - 1]) + 1)
			d->sandbox[i][j] = d->map[i - 1][j - 1];
		d->sandbox[i][j] = 'X';
		d->sandbox[i][++j] = '\0';
		ft_printf("%s\n", d->sandbox[i]);
	}

// última fila: (la única que da SEGV)
	d->sandbox[i] = malloc((int)ft_strlen((d->map[i - 2]) + 2) * sizeof(char));
	if (!d->sandbox[i])
		ft_error_map_data(d, ERROR_MALLOC);
	j = 0;
	while (++j < (int)ft_strlen(d->map[i - 1]) + 1)
		d->sandbox[i][j] = 'X';
	d->sandbox[i][j] = '\0';
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
	//  - (+2) columnas en cada fila
	//  - relleno primera y última fila con 'X'
	//  - relleno primera y última columna con 'X'
	// después, si flood-fill llega hasta alguna X (no cambiar y error)
 * @param d 
 */
void	ft_check_closed_walls(t_data *d)
{
	ft_build_sandbox(d);
//	ft_cub_flood_fill(d->pos.x, d->pos.y, d);
//	ft_print_map(d->sandbox);
	d->sandbox = ft_freedom_null(d->sandbox);
}
