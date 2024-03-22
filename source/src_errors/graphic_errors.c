/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:23:07 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/03/22 18:23:08 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_error_graphic(t_data *d, int error)
{
	if (error == ERROR_MAP_INVALID_TEXTURE_FILE)
		ft_putstr_fd("Error\n Invalid texture file\n", 1);
	ft_free_structs(d);
	exit(42);
}
