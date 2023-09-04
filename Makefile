NAME = cub3D
BONUS = cub3D_bonus

CC = gcc
CFLAGS	:= -Wall -Wextra -Werror

LIBS = MLX42/libmlx42.a MLX42/libglfw3.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit

HEADERS = cub3d.h

SRC = mand/cub3d.c  mand/color.c mand/control.c mand/draw_things.c mand/draw_texture.c mand/raycasting.c mand/utils.c \
		mand/parsing/parsing_Main.c mand/parsing/colors_check.c mand/parsing/map_check.c \
		mand/parsing/basic_functions1.c mand/parsing/basic_functions2.c

SRC_BNS = bonus/cub3d.c  bonus/color.c bonus/control.c bonus/draw_things.c bonus/draw_texture.c bonus/raycasting.c bonus/utils.c \
		bonus/parsing/parsing_Main.c bonus/parsing/colors_check.c bonus/parsing/map_check.c \
		bonus/parsing/basic_functions1.c bonus/parsing/basic_functions2.c

UTL =	mand/utils/get_next_line.c mand/utils/get_next_line_utils.c mand/utils/ft_itoa.c mand/utils/ft_atoi.c\
		mand/utils/ft_memmove.c mand/utils/ft_strdup.c mand/utils/ft_bezero.c mand/utils/ft_strncmp.c mand/utils/ft_isdigit.c

UTL_BNS = bonus/utils/get_next_line.c bonus/utils/get_next_line_utils.c bonus/utils/ft_itoa.c bonus/utils/ft_atoi.c\
		bonus/utils/ft_memmove.c bonus/utils/ft_strdup.c bonus/utils/ft_bezero.c bonus/utils/ft_strncmp.c bonus/utils/ft_isdigit.c

OBJ = ${SRC:.c=.o}
OBJ_BNS = ${SRC_BNS:.c=.o}

UTILS = ${UTL:.c=.o}
UTILS_BNS = ${UTL_BNS:.c=.o}

A = " MOSSY ROCKS "

B = " MOSSY ROCKS BONUS"

all: $(NAME)
	@echo $(A)

bonus: $(BONUS)
	@echo $(B)

$(NAME): $(OBJ) $(UTILS)
	$(CC) $(OBJ) $(UTILS) $(LIBS) -o $(NAME)

$(BONUS): $(OBJ_BNS) $(UTILS_BNS)
	$(CC) -fsanitize=address -g $(OBJ_BNS) $(UTILS_BNS) $(LIBS) -o $(BONUS)

clean:
	@rm -f $(OBJ) $(OBJ_BNS) $(UTILS) $(UTILS_BNS)

fclean: clean 
	@rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean re

my: re 
	@rm -f $(OBJ) $(UTILS) $(OBJ_BNS) $(UTILS_BNS) 
	clear

my_bonus : fclean bonus
	@rm -f $(OBJ) $(UTILS) $(OBJ_BNS) $(UTILS_BNS)
	clear