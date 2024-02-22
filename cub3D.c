#include "includes/cub3D.h"

/* void	ft_graphic(t_data *d)
{
	ft_paint_window(d);
	ft_play_game(d);
} */

// static void	ft_init_data(t_data *d)
// {
// 	d->file = NULL;		// liberar en el parseo (normal y error)
// 	d->map = NULL;		// liberar al cerrar la ventana del juego (?)
// 	d->gnl = NULL;		// liberar tras leer el archivo del mapa
// 	d->tmp = NULL;		// liberar tras su uso temporal
// 	d->sandbox = NULL;	// liberar tras flood-fill
// 	d->path.no = NULL; 	// liberar tras conv_img_to_texture
// 	d->path.so = NULL; 	// liberar tras conv_img_to_texture
// 	d->path.we = NULL; 	// liberar tras conv_img_to_texture
// 	d->path.ea = NULL; 	// liberar tras conv_img_to_texture
// 	d->rgb_c = NULL;	// liberar tras pintar el cielo
// 	d->rgb_f = NULL;	// liberar tras pintar el suelo
// 	d->pos.x = -42;
// 	d->pos.y = -42;
// 	d->pos.d = NONE;
// 	d->flag = 0;		// cd detect 1st map line, check -> (1) = both paths & rgb ok
// }

// void	ft_print_data(t_data *d)
// {
// /* 	ft_printf("FICHERO MAPA:\n");
// 	if (d->map)
// 	{
// 		int i = -1;
// 		while(d->map[++i])
// 			ft_printf("%s\n", d->map[i]);
// 	} */
// 	ft_printf("\n");
// 	ft_printf("FICHERO del mapa:    %s\n", d->file);
// 	ft_printf("FICHERO textura NO:  %s\n", d->path.no);
// 	ft_printf("FICHERO textura SO:  %s\n", d->path.so);
// 	ft_printf("FICHERO textura WE:  %s\n", d->path.we);
// 	ft_printf("FICHERO textura EA:  %s\n", d->path.ea);
// 	ft_printf("FICHERO RGB cielo:   %d,%d,%d\n", d->rgb_c[0], d->rgb_c[1], d->rgb_c[2]);
// 	ft_printf("FICHERO RGB suelo:   %d,%d,%d\n", d->rgb_f[0], d->rgb_f[1], d->rgb_f[2]);
// 	ft_printf("\nFICHERO dir player:  %d\n", d->pos.d);
// 	ft_printf("\nFICHERO coor plyer:  (%d,%d)\n", d->pos.x, d->pos.y);
// }

// static void	ft_parser(t_data *d, char *file)
// {
// 	ft_parse_file_name(d, file);
// 	ft_parse_file_info(d);
// }

// int main(int argc, char **argv)
// {
// 	t_data data;

// 	if (argc == 1)
// 		ft_error_argmts(ERROR_NO_MAP_FILE);
// 	else if (argc > 2)
// 		ft_error_argmts(ERROR_TOO_MANY_ARGMTS);
// 	ft_init_data(&data);
// 	ft_parser(&data, argv[1]);
// //	ft_graphic(&data);
// 	ft_print_data(&data);
// 	ft_free_structs(&data);
// 	return (0);
// }
