/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_free_structs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:29:15 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/03/22 18:29:16 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_structs(t_data *d)
{
	ft_free_null_void_return(&d->path.no);
	ft_free_null_void_return(&d->path.so);
	ft_free_null_void_return(&d->path.we);
	ft_free_null_void_return(&d->path.ea);
	free(d->rgb_f);
	free(d->rgb_c);
	d->map = ft_freedom_null(d->map);
	d->box = ft_freedom_null(d->box);
	free(d->file);
	free(d->gnl);
	free(d->tmp);
}
