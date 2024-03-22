/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:22:58 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/03/22 18:22:59 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

// d->file = NULL;    liberar en el parseo (normal y error)
// d->map = NULL;     liberar al cerrar la ventana del juego (?)
// d->gnl = NULL;     liberar tras leer el archivo del mapa
// d->tmp = NULL;     liberar tras su uso temporal
// d->box = NULL;     liberar tras flood-fill
// d->path.no = NULL; liberar tras conv_img_to_texture
// d->path.so = NULL; liberar tras conv_img_to_texture
// d->path.we = NULL; liberar tras conv_img_to_texture
// d->path.ea = NULL; liberar tras conv_img_to_texture
// d->rgb_c = NULL;   liberar tras pintar el cielo
// d->rgb_f = NULL;   liberar tras pintar el suelo
// d->flag = 0;  cd detect 1st map line, check -> (1) = both paths & rgb ok
static void	ft_init_data(t_data *d)
{
	d->file = NULL;
	d->map = NULL;
	d->gnl = NULL;
	d->tmp = NULL;
	d->box = NULL;
	d->path.no = NULL;
	d->path.so = NULL;
	d->path.we = NULL;
	d->path.ea = NULL;
	d->rgb_c = NULL;
	d->rgb_f = NULL;
	d->hex_c = -42;
	d->hex_f = -42;
	d->ply.pos.x = -42;
	d->ply.pos.y = -42;
	d->ply.dir.x = -42;
	d->ply.dir.y = -42;
	d->ply.cam.x = -42;
	d->ply.cam.y = -42;
	d->flag = 0;
}

static void	ft_parser(t_data *d, char *file)
{
	ft_parse_file_name(d, file);
	ft_parse_file_info(d);
}

void	ft_free_last_textures(t_data *d)
{
	mlx_delete_texture(d->tex.no);
	mlx_delete_texture(d->tex.so);
	mlx_delete_texture(d->tex.ea);
	mlx_delete_texture(d->tex.we);
	mlx_delete_texture(d->tex.mini_r);
	mlx_delete_texture(d->tex.mini_p);
	mlx_delete_texture(d->tex.mini_f);
	mlx_delete_texture(d->tex.mini_w);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1)
		ft_error_argmts(ERROR_NO_MAP_FILE);
	else if (argc > 2)
		ft_error_argmts(ERROR_TOO_MANY_ARGMTS);
	ft_init_data(&data);
	ft_parser(&data, argv[1]);
	ft_graphic(&data);
	ft_free_structs(&data);
	ft_free_last_textures(&data);
	return (0);
}
