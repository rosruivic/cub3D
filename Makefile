
NAME	=	cub3D

SRC		=	cub3D.c \
			parse_file_name.c \
			parse_file_info.c \
			parse_file_get_paths_and_colors.c \
			parse_file_rgb_atoi.c \
			parse_file_get_map.c \
			parse_check_valid_map.c \
			parse_check_closed_walls.c \
			parse_file_free_structs.c \
			parser_errors.c \
			cub_utils.c \
			msh_utils.c

#OBJS	= $(SRC:.c=.o)
OBJS	= $(notdir $(SRC:.c=.o))
OFILES	= $(addprefix obj/, $(OBJS))

CC		= gcc

FLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address

EXTRA	= -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$USER/.brew/opt/glfw/lib/"

# juan-aga memory-leaks tool:
# LEAKS = memory-leaks/memory_leaks.a

LIBFT_PATH = libft/libft.a

MLX42_PATH = MLX42/libmlx42.a

all:	$(NAME)

#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(NAME): $(OFILES) $(LIBFT_PATH)
		$(CC) $(FLAGS) $(OFILES) $(LIBFT_PATH) -o $(NAME)
		clear

#$(NAME): $(OFILES) $(LIBFT_PATH) $(MLX42_PATH)
#		$(CC) $(FLAGS) $(OFILES) $(EXTRA) $(LIBFT_PATH) $(MLX42_PATH) -o $(NAME)
#		clear
		
$(OFILES): $(SRC)
		@mkdir -p obj/
		$(CC) $(FLAGS) -c $(SRC)
# En este código, $< es la primera dependencia (el archivo fuente correspondiente) 
# y $@ es el objetivo (el archivo objeto correspondiente):
#		$(CC) $(FLAGS) -c $< -o $@
		@mv *.o obj/

$(LIBFT_PATH):
		make -C libft all

$(MLX42_PATH):
		make -C MLX42 all

# If a debug with lldb is needed, do 'make' with this rule:
debug: $(LIBFT_PATH) $(MLX42_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(SRC) $(LIBFT_PATH) $(MLX42_PATH) -o $(NAME) -g
		clear

clean:
		rm -rf obj
		make -C libft clean
#		make -C MLX42 clean

fclean: clean
		@make fclean -C libft/
#		@make fclean -C MLX42/
		@rm $(NAME)

re:	fclean all

.PHONY: all clean fclean re
