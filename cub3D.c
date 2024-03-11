#include "includes/cub3D.h"

void	ft_background(t_data *d)
{
	int			i;
	int			j;

	d->background = mlx_new_image(d->mlx, W, H);
	mlx_image_to_window(d->mlx, d->background, 0, 0);
	i = -1;
	j = -1;
	while (++i < H)
	{
		j = -1;
		while (++j < H)
		{
			if (j < H / 2)
				mlx_put_pixel(d->background, i, j, d->hex_c);
			else
				mlx_put_pixel(d->background, i, j, d->hex_f);
		}
	}
}

void	ft_draw(t_data *d, int x, int draw_start, int draw_end)
{
	int			i;

	i = draw_start;
	while (i < draw_end)
	{
		mlx_put_pixel(d->background, x, i, 0xFF0000FF);
		i++;
	}
}

void	ft_raycasting(t_data *d)
{
	int		i;
	double	pos_x;
	int		map_x;
	double	pos_y;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	step_x;
	double	step_y;
	int		hit;
	int		wall_side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;

	wall_side = 0;
	hit = 0;
	step_x = 0;
	step_y = 0;
	i = -1;
	pos_x = d->ply.pos.x;
	pos_y = d->ply.pos.y;
	dir_x = d->ply.dir.x;
	dir_y = d->ply.dir.y;
	plane_x = d->ply.cam.x;
	plane_y = d->ply.cam.y;
	printf("pos:%f,%f, dir:%f,%f, plane:%f,%f\n", pos_x, pos_y, dir_x, dir_y,
			plane_x, plane_y);
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	while (++i < W)
	{
		cam_x = 2 * i / (double)W;
		ray_dir_x = dir_x + plane_x * cam_x;
		ray_dir_y = dir_y + plane_y * cam_x;
		if (ray_dir_x != 0)
			delta_x = fabs(1 / ray_dir_x);
		else
			delta_x = 1e30;
		if (ray_dir_y != 0)
			delta_y = fabs(1 / ray_dir_y);
		else
			delta_y = 1e30;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_x = (pos_x - map_x) * delta_x;
		}
		else if (ray_dir_x > 0)
		{
			step_x = 1;
			side_x = (map_x + 1.0 - pos_x) * delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_y = (pos_y - map_y) * delta_y;
		}
		else if (ray_dir_y > 0)
		{
			step_y = 1;
			side_x = (map_y + 1.0 - pos_y) * delta_y;
		}
		while (hit == 0)
		{
			if (side_x < side_y)
			{
				side_x += delta_x;
				map_x += step_x;
				wall_side = 0;
			}
			else
			{
				side_y += delta_y;
				map_y += step_y;
				wall_side = 1;
			}
			if (map_x <= 0 || map_y <= 0 || d->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (wall_side == 0)
			perp_wall_dist = side_x - delta_x;
		else
			perp_wall_dist = side_y - delta_y;
		line_height = (int)H / perp_wall_dist;
		draw_start = -line_height / 2 + H / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + H / 2;
		if (draw_end >= H)
			draw_end = H - 1;
		ft_draw(d, i, draw_start, draw_end);
	}
}

void	ft_graphic(t_data *d)
{
	d->mlx = mlx_init(H, W, "Cubilete", false);
	ft_background(d);
	ft_raycasting(d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
}

static void	ft_init_data(t_data *d)
{
	d->file = NULL;		// liberar en el parseo (normal y error)
	d->map = NULL;		// liberar al cerrar la ventana del juego (?)
	d->gnl = NULL;		// liberar tras leer el archivo del mapa
	d->tmp = NULL;		// liberar tras su uso temporal
	d->box = NULL;		// liberar tras flood-fill
	d->path.no = NULL; 	// liberar tras conv_img_to_texture
	d->path.so = NULL; 	// liberar tras conv_img_to_texture
	d->path.we = NULL; 	// liberar tras conv_img_to_texture
	d->path.ea = NULL; 	// liberar tras conv_img_to_texture

	d->rgb_c = NULL;	// liberar tras pintar el cielo
	d->rgb_f = NULL;	// liberar tras pintar el suelo
	d->hex_c = -42;
	d->hex_f = -42;
	
	d->ply.pos.x = -42;
	d->ply.pos.y = -42;
	d->ply.dir.x = -42;
	d->ply.dir.y = -42;
	d->ply.cam.x = -42;
	d->ply.cam.y = -42;
	d->flag = 0; // cd detect 1st map line, check -> (1) = both paths & rgb ok
}

void	ft_print_data(t_data *d)
{
	// int	i;
	// ft_printf("FICHERO MAPA:\n");
	// if (d->map)
	// {
	// 	i = -1;
	// 	while(d->map[++i])
	// 		ft_printf("%s\n", d->map[i]);
	// }
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
	ft_print_data(&data);
	ft_free_structs(&data);
	exit(0);
	//	return (0);
}
