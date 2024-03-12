
#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//# include "../../memory-leaks/include/memory_leaks.h"
# define P 64
# define W 1024
# define H 1024
# define TILE 8
# define EXT ".cub"
//# define SECONDS 0.03

typedef enum e_error
{
	NO_ERROR,
	// parser errors (rosana):
	ERROR_NO_MAP_FILE = 100,
	ERROR_TOO_MANY_ARGMTS,
	ERROR_INVALID_FILE_NAME,
	ERROR_MAP_FILE_FD,
	ERROR_FILE_INVALID_ITEM,
	ERROR_FILE_DUPLICATE_TEXTURE,
	ERROR_NORTH_TEXTURE_FILE_FD,
	ERROR_SOUTH_TEXTURE_FILE_FD,
	ERROR_WEST_TEXTURE_FILE_FD,
	ERROR_EAST_TEXTURE_FILE_FD,
	ERROR_INVALID_NUMBER_OF_RGB_ITEMS,
	ERROR_INVALID_RGB_RANGE,
	ERROR_FILE_DUPLICATE_FLOOR_COLOR,
	ERROR_FILE_DUPLICATE_CEILING_COLOR,
	ERROR_MAP_FILE_INCOMPLETE_DATA,
	ERROR_MAP_INVALID_MAP,
	ERROR_MAP_FORBIDDEN_CHAR,
	ERROR_MAP_NO_PLAYER,
	ERROR_MAP_DUPLICATE_PLAYER,
	ERROR_MAP_NO_CLOSED_WALLS,
	ERROR_MALLOC,

	// graphics errors (juan):
	ERROR_GAME_WINDOW = 200,
	ERROR_MAP_INVALID_TEXTURE_FILE,

	END = 999
}					t_error;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_paths
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
}					t_path;

/**
 * @brief 
 * 	N = 0, // dir.x = 0, dir.y = 1
 *	S = 1, // dir.x = 0, dir.y = -1
 *	W = 2, // dir.x = -1, dir.y = 0
 *	E = 3, // dir.x = 1, dir.y = 0
 */
typedef struct s_player
{
	t_point			pos;
	t_point			dir;
	t_point			cam;
}					t_ply;

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_tex;

typedef struct s_image
{
	mlx_image_t		*no;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*ea;
}					t_img;

typedef struct s_data
{
	char			*file;
	int				fd;
	char			*gnl;
	char			*tmp;
	char			**map;
	t_point			dim_map;
	char			**box;
	mlx_t			*mlx;
	t_path			path;
	t_tex			tex;
	t_img			im;
	int				*rgb_c;
	int				*rgb_f;
	uint32_t		hex_c;
	uint32_t		hex_f;
	t_ply			ply;
	mlx_image_t		*background;
	int				flag;
}					t_data;

/* ************************************************************* */
/* ********   100 - CHECKING THE FILE NAME        ************** */
/* ********   & READING THE INFO FROM THE FILE    ************** */
/* ************************************************************* */

void				ft_parse_file_name(t_data *d, char *file);
void				ft_parse_file_info(t_data *d);
void				ft_get_paths_and_colors(t_data *d);
void				ft_rgb_atoi(t_data *d, char camp, char **color);
uint32_t			ft_rgb_to_hex(int r, int g, int b);
void				ft_get_map(t_data *d);

/* ************************************************************* */
/* ********    200 - CHECKING THE INFO OF THE MAP      ********* */
/* ************************************************************* */

void				ft_check_valid_map(t_data *d);
void				ft_check_closed_walls(t_data *d);
void				ft_build_sandbox(t_data *d);

/* ************************************************************* */
/* ************   300 - PAINTING THE GAME WINDOW    ************ */
/* ************************************************************* */

int32_t				ft_paint_window(t_data *d);
void				ft_delete_texture(t_data *d);
void				ft_displ_imgs(t_data *d);

/* ************************************************************* */
/* *************    400 -	PLAYING THE GAME      ************** */
/* ************************************************************* */

void				ft_play_game(t_data *d);

/* ************************************************************* */
/* *************    800 -	ERROR MESSAGES        ************** */
/* ************************************************************* */

void	ft_error_argmts(int error);
void	ft_error_file(t_data *d, int error);
void	ft_error_pull_data(t_data *d, int error);
void	ft_error_pull_map(t_data *d, int error);
void	ft_error_map_data(t_data *d, int error);

/* ************************************************************* */
/* *************           900 - UTILS            ************** */
/* ************************************************************* */

void				ft_free_structs(t_data *d);

char				*ft_delete_nl(char *str);
int					ft_is_str_digits(char *str);
int					ft_matrix_len(char **str);
int					ft_strcmp(char *s1, char *s2);
int					ft_str_equal(char *s1, char *s2);
void				ft_free_null_void_return(char **str);
char				*ft_strjoin_free(char *s1, char *s2);
int					ft_detect_forbidden_chars(char *name);
char				**ft_freedom_null(char **matrix);
void				ft_print_matrix(char **mtx);

/* ************************************************************* */
/* *************           999 - DEBUG            ************** */
/* ************************************************************* */

void				ft_print_data(t_data *d);

#endif
