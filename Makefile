
SRCS = main.c helper_functions.c intersection.c get_texture_color.c scaling.c ray_casting.c angle_directions.c init.c draw_rayes.c make_textures.c \
		intersection_helper.c movement.c movement_helper.c pixel_by_pixel.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		parsing/parsing.c parsing/parsing_utils.c parsing/parsing_utils1.c  get_maps/get_map_utils.c get_maps/get_map_utils1.c\
		get_maps/get_map.c get_maps/init_data.c cleanup/clean_all.c parsing/parsing_utils2.c
OBJS = ${SRCS:.c=.o}

NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -L./minilibx-linux/ -lmlx_Linux -lXext -lX11

LIBFT = libft/libft.a

${NAME}: ${OBJS}
	cd libft && ${MAKE}
	cd minilibx-linux && ${MAKE}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LDFLAGS} -lm -o ${NAME}
all: ${NAME}

clean:
	cd libft && ${MAKE} clean
	rm -f ${OBJS}

fclean: clean
	cd libft && ${MAKE} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
