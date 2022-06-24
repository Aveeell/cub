NAME = cub3D

ADDFLAGS = -lmlx -framework OpenGL -framework AppKit -lz
CLFAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRCS =	main.c \
		check_wall.c \
		check_textures.c \
		get_data_from_file.c \
		utils/ft_split.c \
		utils/ft_strtrim.c \
		utils/ft_atoi.c \
		utils.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

OBJ := $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) $(ADDFLAGS) -o $(NAME)

%.o: %.c cub.h gnl/get_next_line.h Makefile
	$(CC) $(CLFAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus