//#include "../includes/cub3D.h"
#include "includes/cub3D.h"

void	ft_rgb_atoi(t_data *d, char camp, char **color)
{
	int	i;

	i = -1;
	if (camp == 'C')
	{
		d->rgb_c = ft_calloc(3, sizeof(int));
		if (!d->rgb_c)
			ft_error_pull_data(d, ERROR_MALLOC, color);
	}
	else if (camp == 'F')
	{
		d->rgb_f = ft_calloc(3, sizeof(int));
		if (!d->rgb_f)
			ft_error_pull_data(d, ERROR_MALLOC, color);
	}
	while (++i < 3)
	{
		if ((ft_strlen(color[i]) > 3)
			|| (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0))
			ft_error_pull_data(d, ERROR_INVALID_RGB_RANGE, color);
		if (camp == 'C')
			d->rgb_c[i] = ft_atoi(color[i]);
		else if (camp == 'F')
			d->rgb_f[i] = ft_atoi(color[i]);
	}
}
