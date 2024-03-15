#include "cub3D.h"

static void	ft_pull_textures_paths(t_data *d)
{
	if (ft_str_equal(d->box[0], "NO"))
	{
		if (d->path.no)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.no = ft_delete_nl(ft_strdup(d->box[1]));
	}
	else if (ft_str_equal(d->box[0], "SO"))
	{
		if (d->path.so)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.so = ft_delete_nl(ft_strdup(d->box[1]));
	}
	else if (ft_str_equal(d->box[0], "WE"))
	{
		if (d->path.we)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.we = ft_delete_nl(ft_strdup(d->box[1]));
	}
	else if (ft_str_equal(d->box[0], "EA"))
	{
		if (d->path.ea)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_TEXTURE);
		d->path.ea = ft_delete_nl(ft_strdup(d->box[1]));
	}
}

static void	ft_pull_rgb_colors(t_data *d)
{
	char	**rgb;

	d->box[1] = ft_delete_nl(d->box[1]);
	rgb = ft_split(d->box[1], ',');
	if (ft_matrix_len(rgb) != 3)
	{
		rgb = ft_freedom_null(rgb);
		ft_error_pull_data(d, ERROR_INVALID_NUMBER_OF_RGB_ITEMS);
	}
	if (ft_str_equal(d->box[0], "C"))
	{
		if (d->rgb_c)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_CEILING_COLOR);
		ft_rgb_atoi(d, 'C', rgb);
		d->hex_c = ft_rgb_to_hex(d->rgb_c[0], d->rgb_c[1], d->rgb_c[2]);
		printf("hex_c:%x\n", d->hex_c);
	}
	if (ft_str_equal(d->box[0], "F"))
	{
		if (d->rgb_f)
			ft_error_pull_data(d, ERROR_FILE_DUPLICATE_FLOOR_COLOR);
		ft_rgb_atoi(d, 'F', rgb);
		d->hex_f = ft_rgb_to_hex(d->rgb_f[0], d->rgb_f[1], d->rgb_f[2]);
		printf("hex_f:%x\n", d->hex_f);
	}
	rgb = ft_freedom_null(rgb);
}

static void	ft_what_is_this_gnl(t_data *d, char *gnl)
{
	if (gnl[0] == '\n')
		return ;
	d->box = ft_split(gnl, ' ');
	if (ft_matrix_len(d->box) != 2 || (!ft_str_equal(d->box[0], "NO")
			&& !ft_str_equal(d->box[0], "SO") && !ft_str_equal(d->box[0], "WE")
			&& !ft_str_equal(d->box[0], "EA") && !ft_str_equal(d->box[0], "F")
			&& !ft_str_equal(d->box[0], "C")))
		ft_error_file(d, ERROR_FILE_INVALID_ITEM);
	if (ft_strlen(d->box[0]) == 2)
		ft_pull_textures_paths(d);
	else if (ft_strlen(d->box[0]) == 1)
		ft_pull_rgb_colors(d);
	d->box = ft_freedom_null(d->box);
}

static void	ft_determine_flag_status(t_data *d)
{
	if ((d->path.no && d->path.so && d->path.we && d->path.ea) && (d->rgb_c
			&& d->rgb_f))
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
