#include "cub3D.h"
//#include "../includes/cub3D.h"
//#include "includes/cub3D.h"

void ft_error_argmts(int error)
{
	if (error == ERROR_NO_MAP_FILE)
		ft_putstr_fd("Error\n  No map file given\n", 2);
	else if (error == ERROR_TOO_MANY_ARGMTS)
		ft_putstr_fd("Error\n  Too many arguments\n", 2);
	exit(42);
}

void	ft_error_file(t_data *d, int error)
{
	if (error == ERROR_INVALID_FILE_NAME)
		ft_putstr_fd("Error\n  Invalid file name\n", 2);
	else if (error == ERROR_MAP_FILE_FD)
		ft_putstr_fd("Error\n  Map file can't be opened\n", 2);
	else if (error == ERROR_NORTH_TEXTURE_FILE_FD)
		ft_putstr_fd("Error\n  'NO' texture file can't be opened\n", 2);
	else if (error == ERROR_SOUTH_TEXTURE_FILE_FD)
		ft_putstr_fd("Error\n  'SO' texture file can't be opened\n", 2);
	else if (error == ERROR_WEST_TEXTURE_FILE_FD)
		ft_putstr_fd("Error\n  'WE' texture file can't be opened\n", 2);
	else if (error == ERROR_EAST_TEXTURE_FILE_FD)
		ft_putstr_fd("Error\n  'EA' texture file can't be opened\n", 2);
	else if (error == ERROR_MAP_FILE_INCOMPLETE_DATA)
		ft_putstr_fd("Error\n  Map file contains incomplete data\n", 2);
	else if (error == ERROR_FILE_INVALID_ITEM)
		ft_putstr_fd("Error\n  No map or not ordered data\n", 2);
	ft_printf("DEBUG: ft_error_file) error = %d\n", error);
	ft_free_null_void_return(&d->file);
	ft_free_structs(d);
	exit(42);
}
/**
 * @brief 
 * 
 * @param d 
 * @param error 
 * @param mtx 	The path or color returned by ft_split
 */
void	ft_error_pull_data(t_data *d, int error, char **mtx)
{
	if (error == ERROR_FILE_DUPLICATE_TEXTURE)
		ft_putstr_fd("Error\n  Texture direction duplicated\n", 2);
	if (error == ERROR_INVALID_NUMBER_OF_RGB_ITEMS)
		ft_putstr_fd("Error\n  Wrong number of RGB inputs\n", 2);
	if (error == ERROR_FILE_DUPLICATE_CEILING_COLOR)
		ft_putstr_fd("Error\n  Ceiling RGB data duplicated\n", 2);
	if (error == ERROR_FILE_DUPLICATE_FLOOR_COLOR)
		ft_putstr_fd("Error\n  Floor RGB data duplicated\n", 2);
	if (error == ERROR_INVALID_RGB_RANGE)
		ft_putstr_fd("Error\n  RGB number out of range\n", 2);
	if (error == ERROR_MALLOC)
		ft_putstr_fd("Error\n  Allocating memory fail\n", 2);
	ft_printf("DEBUG: ft_error_pull_data)\n");
	mtx = ft_freedom_null(mtx);
	close(d->fd);
	ft_free_structs(d);
	exit(42);
}

void	ft_error_pull_map(t_data *d, int error)
{
	if (error == ERROR_MAP_FILE_INCOMPLETE_DATA)
		ft_putstr_fd("Error\n  No map\n", 2);
	if (error == ERROR_MAP_INVALID_MAP)
		ft_putstr_fd("Error\n  Invalid map\n", 2);
	ft_printf("DEBUG: ft_error_pull_map)\n");
	close(d->fd);
	ft_free_structs(d);
	exit(42);
}

void	ft_error_map_data(t_data *d, int error)
{
	if (error == ERROR_MAP_FORBIDDEN_CHAR)
		ft_putstr_fd("Error\n  Map contains forbidden chars\n", 2);
	if (error == ERROR_MAP_NO_PLAYER)
		ft_putstr_fd("Error\n  No player detected\n", 2);
	if (error == ERROR_MAP_DUPLICATE_PLAYER)
		ft_putstr_fd("Error\n  More than 1 player detected\n", 2);
	if (error == ERROR_MALLOC)
		ft_putstr_fd("Error\n  Allocating memory fail\n", 2);
	if (error == ERROR_MAP_NO_CLOSED_WALLS)
		ft_putstr_fd("Error\n  Map isn't completely rounded by walls\n", 2);
	ft_printf("DEBUG: ft_error_map_data)\n");
	ft_free_structs(d);
	exit(42);
}
