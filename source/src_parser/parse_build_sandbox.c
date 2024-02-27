#include "cub3D.h"

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
		d->sandbox[i] = malloc((ft_longer_row(d) + 3) * sizeof(char));
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

	d->sandbox[i] = malloc((ft_longer_row(d) + 3) * sizeof(char));
	if (!d->sandbox[i])
		ft_error_map_data(d, ERROR_MALLOC);
	j = -1;
	while (++j < ft_longer_row(d) + 2)
		d->sandbox[i][j] = 'X';
	d->sandbox[i][j] = '\0';
}

void	ft_build_sandbox(t_data *d)
{
	int	rows;
	int	i;

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
