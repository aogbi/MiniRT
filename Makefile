# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:19:59 by rpinto-r          #+#    #+#              #
#    Updated: 2025/01/02 01:30:45 by aogbi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC               = gcc
CFLAGS           = #-Werror -Wextra -Wall
CDEBUG           = -g3 -fsanitize=address
RM               = rm -rf
NAME             = minirt
SRCS_DIR         = ./srcs
SRCS_INC         = ./includes
SRCS             = $(wildcard *.c)
OBJS             = $(SRCS:.c=.o)
SCENE		     = ./scenes/mandatory.rt

### LIBRARIES ###
LIBFT_FLAGS      = -lft
LIBFT_DIR        = Libft
# ifeq ($(shell uname), Linux)
LIBMLX_DIR   = ./libmlx/linux
LIBMLX_FLAGS = -lmlx -lXext -lX11 -lm -lz
# else
# 	LIBMLX_DIR   = ./libmlx/macos
# 	LIBMLX_FLAGS = -lmlx -framework openGL -framework AppKit
# endif


### RULES ###
all: $(NAME)

.c.o:
	$(CC) -I $(SRCS_INC) -I $(LIBMLX_DIR) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) addons
	$(MAKE) -C $(LIBMLX_DIR)
	$(CC) -g3 $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME) 
	# $(SCENE)

dev: CFLAGS += $(CDEBUG)
dev: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -o $(NAME)
	$(MAKE) run

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re