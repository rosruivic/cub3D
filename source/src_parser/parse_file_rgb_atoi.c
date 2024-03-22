/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_rgb_atoi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:06 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/03/22 18:30:16 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	ft_rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 24) | ((g & 0xFF) << 16)
		| ((b & 0xFF) << 8) | (0xFF));
}

void	ft_rgb_atoi(t_data *d, char camp, char **color)
{
	int	i;

	i = -1;
	if (camp == 'C')
	{
		d->rgb_c = ft_calloc(3, sizeof(int));
		if (!d->rgb_c)
			ft_error_pull_data(d, ERROR_MALLOC);
	}
	else if (camp == 'F')
	{
		d->rgb_f = ft_calloc(3, sizeof(int));
		if (!d->rgb_f)
			ft_error_pull_data(d, ERROR_MALLOC);
	}
	while (++i < 3)
	{
		if ((ft_strlen(color[i]) > 3 || !ft_is_str_digits(color[i]))
			|| (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0))
			ft_error_pull_data(d, ERROR_INVALID_RGB_RANGE);
		if (camp == 'C')
			d->rgb_c[i] = ft_atoi(color[i]);
		else if (camp == 'F')
			d->rgb_f[i] = ft_atoi(color[i]);
	}
}
