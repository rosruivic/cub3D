//#include "../includes/cub3D.h"
//#include "includes/cub3D.h"
#include "cub3D.h"

static void	ft_pull_textures_paths(t_data *d, char **tex)
{
	if (ft_str_equal(tex[0], "NO"))
	{
		if (d->path.no)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE, tex);
		d->path.no = ft_delete_nl(ft_strdup(tex[1]));
	}
	else if (ft_str_equal(tex[0], "SO"))
	{
		if (d->path.so)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE, tex);
		d->path.so = ft_delete_nl(ft_strdup(tex[1]));
	}
	else if (ft_str_equal(tex[0], "WE"))
	{
		if (d->path.we)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE, tex);
		d->path.we = ft_delete_nl(ft_strdup(tex[1]));
	}
	else if (ft_str_equal(tex[0], "EA"))
	{
		if (d->path.ea)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE, tex);
		d->path.ea = ft_delete_nl(ft_strdup(tex[1]));
	}
}

static void	ft_pull_rgb_colors(t_data *d, char **color)
{
	char	**rgb;

	rgb = ft_split(color[1], ',');
/* 	ft_printf("DEBUG: ft_pull_rgb_colors) %s rgb[0] = %s\n", color[0], rgb[0]);
	ft_printf("DEBUG: ft_pull_rgb_colors) %s rgb[1] = %s\n", color[0], rgb[1]);
	ft_printf("DEBUG: ft_pull_rgb_colors) %s rgb[2] = %s\n----\n", color[0], rgb[2]); */
	if (ft_matrix_len(rgb) != 3 || ft_str_equal(rgb[2], "\n"))
	{
		rgb = ft_freedom_null(rgb);
		ft_error_pull_data(d, ERROR_INVALID_NUMBER_OF_RGB_ITEMS, color);
	}
	rgb[2] = ft_delete_nl(ft_strdup(rgb[2]));
	if (ft_str_equal(color[0], "C"))
	{
		if (d->rgb_c)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_CEILING_COLOR, color);
		ft_rgb_atoi(d, 'C', rgb);
	}
	if (ft_str_equal(color[0], "F"))
	{
		if (d->rgb_f)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_FLOOR_COLOR, color);
		ft_rgb_atoi(d, 'F', rgb);
	}
}

static void	ft_what_is_this_gnl(t_data *d, char *gnl)
{
	char	**item;

	if (gnl[0] == '\n')
		return ;
	item = ft_split(gnl, ' ');
	if (ft_matrix_len(item) != 2 && !d->flag)
	{
		item = ft_freedom_null(item);
		ft_error_file(d, ERROR_FILE_INVALID_ITEM);
	}
	if (ft_strlen(item[0]) == 2)
	{
		if (!ft_str_equal(item[0], "NO") && !ft_str_equal(item[0], "SO")
			&& !ft_str_equal(item[0], "WE") && !ft_str_equal(item[0], "EA"))
			ft_error_file(d, ERROR_FILE_INVALID_ITEM);
		ft_pull_textures_paths(d, item);
	}
	else if (ft_strlen(item[0]) == 1)
	{
		if (!ft_str_equal(item[0], "F") && !ft_str_equal(item[0], "C"))
			ft_error_file(d, ERROR_FILE_INVALID_ITEM);
		ft_pull_rgb_colors(d, item);
	}
	item = ft_freedom_null(item);
}

static void	ft_determine_flag_status(t_data *d)
{
	if ((d->path.no && d->path.so && d->path.we && d->path.ea)
		&& (d->rgb_c && d->rgb_f))
		d->flag = 1;
}

/**
 * @brief 
 *  WHILE Boucle: 
 * 	- inside its functions, if a map line is detected -> error + exit
 * 	- when all paths & colors are completed, flag = 1 finish the boucle
 *  - if file ends (gnl = NULL) & flag = 0, breaks
 * @param d 
 */
void	ft_get_paths_and_colors(t_data *d)
{
	char	*gnl;

	while (d->flag == 0)
	{
		gnl = get_next_line(d->fd);
		if (!gnl)
			break ;
		ft_what_is_this_gnl(d, gnl);
		ft_free_null_void_return(&gnl);
		ft_determine_flag_status(d);
	}
	if (!d->flag)
		ft_error_file(d, ERROR_MAP_FILE_INCOMPLETE_DATA);
}
