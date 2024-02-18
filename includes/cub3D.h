
#ifndef CUB_3D_H
# define CUB_3D_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# define P 64
# define EXT ".cub"
//# define SECONDS 0.03

typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_dir;

typedef enum e_error
{
	NO_ERROR,
	// parser errors (rosana):
	ERROR_NO_MAP_FILE = 100,
	ERROR_TOO_MANY_ARGMTS,
	ERROR_INVALID_FILE_NAME,
	ERROR_FILE_FD,
	ERROR_EMPTY_FILE,
	ERROR_FILE_INVALID_ITEM,
	ERROR_FILE_DUPLICATE_TEXTURE,
	ERROR_NORTH_TEXTURE_FILE_FD,
	ERROR_SOUTH_TEXTURE_FILE_FD,
	ERROR_WEST_TEXTURE_FILE_FD,
	ERROR_EAST_TEXTURE_FILE_FD,
	ERROR_INVALID_RGB_NUMBER,
	ERROR_INVALID_RGB_RANGE,
//	ERROR_FILE_SAME_COLOR_FLOOR_CEILING,
	ERROR_FILE_DUPLICATE_FLOOR_COLOR,
	ERROR_FILE_DUPLICATE_CEILING_COLOR,
	ERROR_MISSING_ITEM_FLOOR_COLOR,
	ERROR_MISSING_ITEM_CEILING_COLOR,
	ERROR_MAP_EMPTY_LINE,
	ERROR_MAP_FORBIDDEN_CHAR,
	ERROR_MAP_NO_PLAYER,
	ERROR_MAP_NO_CLOSED_MAP,

	// game errors (juan):
	ERROR_GAME_WINDOW = 200,
	ERROR_MAP_INVALID_TEXTURE_FILE,

	END = 999
}	t_error;


typedef struct s_paths
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}		t_path;

typedef struct s_player
{
	int	x;
	int	y;
	int	dir;
}		t_ply;

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_tex;

typedef struct s_image
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
}				t_img;

typedef struct s_data
{
	char	*file;
	int		fd;
	char	**map;
	char	**twin_map;
	mlx_t	*mlx;
	t_path	path;
	t_tex	tex;
	t_img	im;
	int		*rgb_c;
	int		*rgb_f;
	t_ply 	pos;
}			t_data;

/* ************************************************************* */
/* ********   100 - CHECKING THE FILE NAME        ************** */
/* ********   & READING THE INFO FROM THE FILE    ************** */
/* ************************************************************* */

void	ft_parse_file_name(t_data *d, char *file);
void	ft_parse_file_info(t_data *d);

/* ************************************************************* */
/* ********    200 - CHECKING THE INFO OF THE FILE     ********* */
/* ************************************************************* */

void	ft_check_map(t_data *d);
void	ft_loc_player(t_data *d);
void	ft_right_path(t_data *d);

/* ************************************************************* */
/* ************   300 - PAINTING THE GAME WINDOW    ************ */
/* ************************************************************* */

int32_t	ft_paint_window(t_data *d);
void	ft_delete_texture(t_data *d);
void	ft_displ_imgs(t_data *d);

/* ************************************************************* */
/* *************    400 -	PLAYING THE GAME      ************** */
/* ************************************************************* */

void	ft_play_game(t_data *d);

/* ************************************************************* */
/* *************    800 -	ERROR MESSAGES        ************** */
/* ************************************************************* */

void	ft_error_argmts(int error);
void	ft_error_file(t_data *d, int error);

/* ************************************************************* */
/* *************           900 - UTILS            ************** */
/* ************************************************************* */

char	*ft_delete_nl(char *str)

#endif
