# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 13:05:18 by mkoch             #+#    #+#              #
#    Updated: 2022/07/08 13:05:19 by mkoch            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

ADDFLAGS = -lmlx -framework OpenGL -framework AppKit -lz
CLFAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRCS =	main.c \
		check_wall.c \
		check_textures.c \
		free_and_error.c \
		get_map_position.c \
		create_struct_all.c \
		get_data_from_file.c \
		check_spaces_n_zeros.c \
		utils.c \
		utils/ft_atoi.c \
		utils/ft_split.c \
		utils/ft_strtrim.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		move.c \
		minimap.c \
		cast_ray.c \
		draw_column.c \
		hook_and_render.c \
		mouse.c \
		

OBJ := $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CLFAGS) $(OBJ) $(ADDFLAGS) -o $(NAME)

%.o: %.c cub.h gnl/get_next_line.h Makefile
	$(CC) $(CLFAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus