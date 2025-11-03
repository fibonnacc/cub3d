# Executable name
NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -I./minilibx-linux -L./minilibx-linux -lmlx -lXext -lX11

# Directories

GET_NEXT_LINE_DIR = ./get_next_line
# Libraries
# -L tells the linker where to look for library files.

LDFLAGS = -L. -lmlx -lX11 -lXext -lm $(PRINTF_LIB)
GET_NEXT_LINE_SRCS = 	$(GET_NEXT_LINE_DIR)/get_next_line.c \
						$(GET_NEXT_LINE_DIR)/get_next_line_utils.c

# Source files for mandatory version
CUB3D_SRCS = main.c helper_functions.c
SRCS = $(GET_NEXT_LINE_SRCS) $(CUB3D_SRCS)
OBJS = $(SRCS:.c=.o)

# Rules mandatory

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(OBJS) $(LDFLAGS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include/minilibx-linux -c $< -o $@

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

.SECONDARY : $(OBJS)
.PHONY: all clean fclean re
