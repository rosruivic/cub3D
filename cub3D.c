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

void	ft_print_data(t_data *d)
{
	ft_printf("\n");
	ft_printf("FICHERO del mapa:        %s\n", d->file);
	ft_printf("FICHERO textura NO:      %s\n", d->path.no);
	ft_printf("FICHERO textura SO:      %s\n", d->path.so);
	ft_printf("FICHERO textura WE:      %s\n", d->path.we);
	ft_printf("FICHERO textura EA:      %s\n", d->path.ea);
	ft_printf("FICHERO RGB cielo:       %d,%d,%d\n", d->rgb_c[0], d->rgb_c[1],
			d->rgb_c[2]);
	printf("FICHERO RGB hex cielo:   %06X\n", d->hex_c);
	ft_printf("FICHERO RGB suelo:       %d,%d,%d\n", d->rgb_f[0], d->rgb_f[1],
			d->rgb_f[2]);
	printf("FICHERO RGB hex suelo:   %06X\n", d->hex_f);
	ft_printf("\nFICHERO coor plyer:   (%d,%d)\n", d->ply.pos.x, d->ply.pos.y);
	ft_printf("\nFICHERO dir player:   (%d,%d)\n", d->ply.dir.x, d->ply.dir.y);
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

void	ft_l(void)
{
	system("leaks -q cub3D");
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(ft_l);
	if (argc == 1)
		ft_error_argmts(ERROR_NO_MAP_FILE);
	else if (argc > 2)
		ft_error_argmts(ERROR_TOO_MANY_ARGMTS);
	ft_init_data(&data);
	ft_parser(&data, argv[1]);
	ft_graphic(&data);
	ft_print_data(&data);
	ft_free_structs(&data);
	ft_free_last_textures(&data);
	return (0);
}
