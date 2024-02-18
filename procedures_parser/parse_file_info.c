#include "../includes/cub3D.h"

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

static void	ft_pull_textures_paths(t_data *d, char **tex)
{
	if (ft_str_equal(tex[0], "NO"))
	{
		if (d->path.no)
			ft_error_file(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.no = ft_delete_nl(ft_strdup(tex[1]));
	}
	else if (ft_str_equal(tex[0], "SO"))
	{
		if (d->path.so)
			ft_error_file(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.so = ft_delete_nl(ft_strdup(tex[1]));
	}
	else if (ft_str_equal(tex[0], "WE"))
	{
		if (d->path.we)
			ft_error_file(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.we = ft_delete_nl(ft_strdup(tex[1]));
	}
	else if (ft_str_equal(tex[0], "EA"))
	{
		if (d->path.ea)
			ft_error_file(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.ea = ft_delete_nl(ft_strdup(tex[1]));
	}
}

static void	ft_pull_rgb_colors(t_data *d, char **color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(color[1], ',');
	if (ft_matrix_len(rgb) != 3)
	{
		ft_freedom_null(rgb);
		ft_error_file(d, ERROR_INVALID_RGB_NUMBER) ;
	}
	if (ft_str_equal(color[0], "C"))
		if (d->rgb_c)
			ft_error_file(d, ERROR_FILE_DUPLICATE_CEILING_COLOR);
	if (ft_str_equal(color[0], "F"))
		if (d->rgb_f)
			ft_error_file(d, ERROR_FILE_DUPLICATE_FLOOR_COLOR);
	while (color[++i])
		ft_del_spcs_start_end(d, color[i]);
}

static void	ft_what_is_gnl(t_data *d, char *gnl)
{
	char	**item;

	if (gnl[0] == '\n')
		return ;
	item = ft_split(gnl, ' ');
	if (ft_matrix_len(item) != 2)
	{
		ft_freedom_null(item);
		return ;
	}
	if (ft_strlen(item[0]) == 2)
	{
		if (!ft_str_equal(item[0]), "F" && !ft_str_equal(item[0]), "C")
			ft_error_file(d, ERROR_FILE_INVALID_ITEM);
		ft_pull_textures_paths(d, item);
	}
	else if (ft_strlen(item[0]) == 1)
		ft_pull_rgb_colors(d, item);
}

void	ft_parse_file_info(t_data *d)
{
	char	*gnl;

	d->fd = open(d->file, O_RDONLY);
	if (d->fd < 0)
		ft_error_file(d, ERROR_FILE_FD);
	while (1)
	{
		gnl = get_next_line(d->fd);
		if (!gnl)
			break ;
		ft_what_is_gnl(d, gnl);
		ft_free_null_void_return(gnl);
	}
	ft_check_valid_files(d);
	ft_check_valid_colors(d);
	ft_get_map(d);
	close(d->fd);
}
