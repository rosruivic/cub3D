#include "../includes/cub3D.h"

void ft_error_argmts(int error)
{
	if (error == ERROR_NO_MAP_FILE)
		ft_putstr_fd("Error\nNo map file given\n", 2);
	else if (error == ERROR_TOO_MANY_ARGMTS)
		ft_putstr_fd("Error\nToo many arguments\n", 2);
	exit(1);
}

void	ft_error_file(t_data *d, int error)
{
	if (error == ERROR_INVALID_FILE_NAME)
		ft_putstr_fd("Error\nInvalid file name\n", 2);
	else if (error == ERROR_FILE_FD)
		ft_putstr_fd("Error\nFile doesn't exist or can't be opened\n", 2);
	else if (error == ERROR_EMPTY_FILE)
		ft_putstr_fd("Error\nFile is empty\n", 2);
	ft_free_null_void_return(&d->file);
	exit(1);
}
