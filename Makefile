NAME = cub3d
#CC = gcc
#CFLAGS	:= -Wall -Wextra -Werror

LIBS = MLX42/libmlx42.a MLX42/libglfw3.a -Iinclude -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
#-Iinclude -ldl -lglfw -pthread -lm

HEADERS = cub3d.h
SRC = cub3d.c draw_line.c color.c
#SRC_B = fdf_bonus.c bonus/draw_line_bonus.c bonus/read_grid_bonus.c bonus/draw_grid_bonus.c bonus/color_bonus.c\
#		bonus/interface.c bonus/control.c bonus/control2.c
UTL =	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c utils/ft_strlen.c

OBJ = ${SRC:.c=.o}
#OBJ_B = ${SRC_B:.c=.o}
UTILS = ${UTL:.c=.o}

G = " MOSSY ROCK "

all: $(NAME)
	@echo $(G)

$(NAME): $(OBJ) $(UTILS)
	$(CC) $(OBJ) $(UTILS) $(LIBS) -o $(NAME)

#bonus: $(BONUS)
#	@echo $(FMW_B)

#$(BONUS): $(OBJ_B) $(UTILS)
#	$(CC) $(OBJ_B) $(UTILS) $(LIBS) -o $(BONUS)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B) $(UTILS) 

fclean: clean 
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean re
