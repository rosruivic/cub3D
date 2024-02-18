#include "includes/cub3D.h"

/* void	ft_graphic(t_data *d)
{
	ft_paint_window(d);
	ft_play_game(d);
} */

static void	ft_parser(t_data *d, char *file)
{
	ft_parse_file_name(d, file);
	ft_parse_file_info(d);
}

static void	ft_init_data(t_data *d)
{
	d->file = NULL;		// liberar en el parseo (normal y error)
	d->map = NULL;		// liberar al cerrar la ventana del juego (?)
	d->twin_map = NULL;	// liberar tras flood-fill
	d->path.no = NULL; 	// liberar tras conv_img_to_texture
	d->path.so = NULL; 	// liberar tras conv_img_to_texture
	d->path.we = NULL; 	// liberar tras conv_img_to_texture
	d->path.ea = NULL; 	// liberar tras conv_img_to_texture
	d->rgb_c = NULL;	// liberar tras pintar el cielo
	d->rgb_f = NULL;	// liberar tras pintar el suelo
	d->flag = 0;		// cd detect 1st map line, check -> (1) = both paths & rgb ok
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc == 1)
		ft_error_argmts(ERROR_NO_MAP_FILE);
	else if (argc > 2)
		ft_error_argmts(ERROR_TOO_MANY_ARGMTS);
	ft_init_data(&data);
	ft_parser(&data, argv[1]);
//	ft_graphic(&data);
	ft_free_structs(&data);
	return (0);
}
