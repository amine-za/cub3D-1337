NAME = cub3D

CC = cc
CFLAGS	:= -Wall -Wextra -Werror

LIBS = MLX42/libmlx42.a MLX42/libglfw3.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit

HEADERS = cub3d.h

SRC = cub3d.c  color.c control.c draw_things.c draw_texture.c raycasting.c utils.c \
		parsing/parsing_Main.c parsing/colors_check.c parsing/map_check.c \
		parsing/basic_functions1.c parsing/basic_functions2.c

UTL =	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c\
		utils/ft_memmove.c utils/ft_strdup.c utils/ft_bezero.c utils/ft_strncmp.c utils/ft_isdigit.c

OBJ = ${SRC:.c=.o}
UTILS = ${UTL:.c=.o}

A = "Cube 3D"

all: $(NAME)
	@echo $(A)

$(NAME): $(OBJ) $(UTILS)
	$(CC) $(OBJ) $(UTILS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ) $(UTILS)

fclean: clean 
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean re

my: re 
	@rm -f $(OBJ) $(UTILS)
	clear

