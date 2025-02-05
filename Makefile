# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:32:15 by luiberna          #+#    #+#              #
#    Updated: 2025/02/05 18:39:27 by luiberna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = main.c utils.c map.c map_utils.c textures.c free.c minimap.c movement.c \
		init.c init_aux.c check.c keys.c color.c draw.c raycasting.c clear.c \
		

CC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = ./Includes/

CFLAGS = -I$(INCLUDE) -g -I$(MINILIBX) -O3

LIB_MINILIBX = $(MINILIBX)/libmlx_Linux.a -L$(MINILIBX) -L/usr/lib -I$(MINILIBX) -lXext -lX11 -lm -lz

MINILIBX = ./minilibx-linux/

RM = rm -f

GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(RESET)"
	@make -C ./Libft > /dev/null 2>&1
	@make -C $(MINILIBX) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME) $(LIB_MINILIBX)  > /dev/null 2>&1
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null
	@echo "$(YELLOW)Compiling $@...$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C ./Libft > /dev/null 2>&1
	@make clean -C $(MINILIBX) > /dev/null 2>&1
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@make fclean -C ./Libft > /dev/null 2>&1
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re






