//#include "../includes/cub3D.h"
#include "includes/cub3D.h"

/* Si falla malloc, exit directo pq no hay nada que liberar hasta ahora */
void	ft_parse_file_name(t_data *d, char *file)
{
	if (ft_strlen(file) < 5
		|| !ft_str_equal(ft_strrchr((const char *)file, '.'), EXT))
		ft_error_file(d, ERROR_INVALID_FILE_NAME);
	d->file = ft_strdup(file);
	if (!d->file)
		exit (1);
}
