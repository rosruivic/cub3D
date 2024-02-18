//#include "../includes/cub3D.h"
#include "includes/cub3D.h"

static void	ft_check_valid_files(t_data *d)
{
	int	fd;

	fd = open(d->path.no, O_RDONLY);
	if (fd < 0)
		ft_error_file(d, ERROR_NORTH_TEXTURE_FILE_FD);
	close(fd);
	fd = open(d->path.so, O_RDONLY);
	if (fd < 0)
		ft_error_file(d, ERROR_SOUTH_TEXTURE_FILE_FD);
	close(fd);
	fd = open(d->path.we, O_RDONLY);
	if (fd < 0)
		ft_error_file(d, ERROR_WEST_TEXTURE_FILE_FD);
	close(fd);
	fd = open(d->path.ea, O_RDONLY);
	if (fd < 0)
		ft_error_file(d, ERROR_EAST_TEXTURE_FILE_FD);
	close(fd);
}

static void	ft_check_valid_colors(t_data *d)
{
	(void)d;
}

void	ft_parse_file_info(t_data *d)
{
	d->fd = open(d->file, O_RDONLY);
	if (d->fd < 0)
		ft_error_file(d, ERROR_MAP_FILE_FD);
	ft_get_paths_and_colors(d);
	ft_check_valid_files(d);
	ft_check_valid_colors(d);
//	ft_get_map(d);
	close(d->fd);
}
