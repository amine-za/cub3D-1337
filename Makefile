NAME = cub3d
#CC = gcc
#CFLAGS	:= -Wall -Wextra -Werror

LIBS = MLX42/libmlx42.a MLX42/libglfw3.a -Iinclude -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
#-Iinclude -ldl -lglfw -pthread -lm

HEADERS = cub3d.h
SRC = cub3d.c color.c\
		pars_map.c pars_clrs.c\
		control.c draw_things.c draw_texture.c\
		raycasting.c utils.c\
		# chyata.c
#SRC_B = 
UTL =	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c\
		utils/ft_memmove.c utils/ft_strdup.c utils/ft_bezero.c utils/ft_strncmp.c\

OBJ = ${SRC:.c=.o}
#OBJ_B = ${SRC_B:.c=.o}
UTILS = ${UTL:.c=.o}

G = " MOSSY ROCKS "

all: $(NAME)
	@echo $(G)

$(NAME): $(OBJ) $(UTILS)
	$(CC) $(OBJ) $(UTILS) $(LIBS) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(UTILS) 

fclean: clean 
	@rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean re

my: re 
	@rm -f $(OBJ) $(UTILS) 
	clear
