# --- Colors ---

BOLD      := \033[1m
BLACK     := \033[30;1m
RED       := \033[31;1m
GREEN     := \033[32;1m
YELLOW    := \033[33;1m
BLUE      := \033[34;1m
MAGENTA   := \033[35;1m
CYAN      := \033[36;1m
WHITE     := \033[37;1m
RESET     := \033[0m

NAME	=	cub3D

SRC		=	cub3D.c \
			parse_file_name.c \
			parse_file_info.c \
			parse_file_get_paths_and_colors.c \
			parse_file_rgb_atoi.c \
			parse_file_get_map.c \
			parse_check_valid_map.c \
			parse_check_closed_walls.c \
			parse_build_sandbox.c \
			parse_file_free_structs.c \
			parser_errors.c \
			cub_utils.c \
			msh_utils.c \
			msh_utils_free_null.c \
			msh_utils_str_cmp_equal.c \
			prueba.c \

OBJS	= $(SRC:.c=.o)
#OBJS	= $(notdir $(SRC:.c=.o))
OFILES	= $(addprefix obj/, $(OBJS))

CC		= gcc

FLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address

EXTRA	= -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

# juan-aga memory-leaks tool:
# LEAKS = memory-leaks/memory_leaks.a

LIBFT_PATH = libft/libft.a

MLX42_PATH = MLX42/libmlx42.a

HEADERS = -I ./includes

all:	$(NAME)

vpath %.c source/src_parser source/src_errors source/src_graphics source/src_utils

#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(OFILES): obj/%.o: %.c
		@mkdir -p obj
		@$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OFILES) $(LIBFT_PATH) $(MLX42_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(OFILES) $(LIBFT_PATH) $(MLX42_PATH) $(HEADERS) -o $(NAME)
		clear

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
		# make -C MLX42 clean

fclean: clean
		@make fclean -C libft/
		# @make fclean -C MLX42/
		@rm -rf $(NAME)

re:	fclean all

norma:
	@echo "$(BLUE)$(BOLD)Checking norminette...$(RESET)"
	@norminette src/* include/*

.PHONY: all clean fclean re
