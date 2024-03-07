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

	d->box[0] = malloc((ft_longer_row(d) + 2 + 1) * sizeof(char));
	if (!d->box[0])
		ft_error_map_data(d, ERROR_MALLOC);
	j = -1;
	while (++j < ft_longer_row(d) + 2)
		d->box[0][j] = 'X';
	d->box[0][j] = '\0';
	ft_printf("%s\n", d->box[0]);
}

static int	ft_build_sandbox_inter_lines(t_data *d, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (++i < rows - 2)
	{
		j = 0;
		d->box[i] = malloc((ft_longer_row(d) + 3) * sizeof(char));
		if (!d->box[i])
			ft_error_map_data(d, ERROR_MALLOC);
		d->box[i][0] = 'X';
		while (++j < (int)ft_strlen(d->map[i - 1]) + 1)
			d->box[i][j] = d->map[i - 1][j - 1];
		d->box[i][j] = 'X';
		while (++j < ft_longer_row(d) + 2)
			d->box[i][j] = 'X';
		d->box[i][j] = '\0';
		ft_printf("%s\n", d->box[i]);
	}
	return (i);
}

static void	ft_build_sandbox_last_line(t_data *d, int i)
{
	int	j;

	d->box[i] = malloc((ft_longer_row(d) + 3) * sizeof(char));
	if (!d->box[i])
		ft_error_map_data(d, ERROR_MALLOC);
	j = -1;
	while (++j < ft_longer_row(d) + 2)
		d->box[i][j] = 'X';
	d->box[i][j] = '\0';
}

void	ft_build_sandbox(t_data *d)
{
	int	rows;
	int	i;

	rows = ft_matrix_len(d->map) + 2 + 1;
	d->box = calloc((rows + 1), sizeof(char *));
	if (!d->box)
		ft_error_map_data(d, ERROR_MALLOC);
	d->box[rows] = NULL;
	ft_build_sandbox_first_line(d);
	i = ft_build_sandbox_inter_lines(d, rows);
	ft_build_sandbox_last_line(d, i);
	ft_printf("%s\n", d->box[i]);
	ft_printf("\n");
}
