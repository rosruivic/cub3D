//#include "../includes/cub3D.h"
#include "includes/cub3D.h"

void	ft_free_structs(t_data *d)
{
	ft_free_null_void_return(&d->path.no);
	ft_free_null_void_return(&d->path.so);
	ft_free_null_void_return(&d->path.we);
	ft_free_null_void_return(&d->path.ea);
	free(d->rgb_f);
	free(d->rgb_c);
}
