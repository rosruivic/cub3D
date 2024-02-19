//#include "../includes/cub3D.h"
#include "includes/cub3D.h"

static void	ft_reading_map(t_data *d)
{
	d->tmp = ft_strjoin_free(d->tmp, d->gnl);
	ft_free_null_void_return(&d->gnl);
	while (1)
	{
		d->gnl = get_next_line(d->fd);
		if (!d->gnl)
			break ;
		if (ft_str_equal(d->gnl, "\n"))
		{
			ft_free_null_void_return(&d->tmp);
			ft_free_null_void_return(&d->gnl);
			ft_error_pull_map(d, ERROR_MAP_INVALID_MAP);
		}
		d->tmp = ft_strjoin_free(d->tmp, d->gnl);
		ft_free_null_void_return(&d->gnl);
	}
}

void	ft_get_map(t_data *d)
{
	while (1)
	{
		d->gnl = get_next_line(d->fd);
		if (!d->gnl || !ft_str_equal(d->gnl, "\n"))
			break ;
	}
	if (d->gnl)
		ft_reading_map(d);
	if (!d->tmp)
		ft_error_pull_map(d, ERROR_MAP_FILE_INCOMPLETE_DATA);
	d->map = ft_split(d->tmp, '\n');
	ft_free_null_void_return(&d->tmp);
}
