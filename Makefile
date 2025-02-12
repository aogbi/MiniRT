# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:19:59 by rpinto-r          #+#    #+#              #
#    Updated: 2025/02/12 20:27:52 by aogbi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC               = cc
CFLAGS           = -Werror -Wextra -Wall
RM               = rm -rf
NAME             = minirt
SRCS_INC         = ./includes
SRCS             = ./srcs/get_scene_description.c\
				   ./srcs/main.c\
				   ./srcs/vec3.c
OBJS             = $(SRCS:.c=.o)
SCENE		     = ./scenes/mandatory.rt

LIBFT_DIR        = libft
LIBFT_FLAGS      = -lft
LIBMLX_DIR   = mlx
LIBMLX_FLAGS = -lmlx -lXext -lX11 -lm -lz


all: $(NAME)

.c.o:
	$(CC) -I $(SRCS_INC) -I $(LIBMLX_DIR) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBMLX_DIR)
	$(MAKE) -C $(LIBFT_DIR) addons
	$(CC) -O3 $(OBJS) $(CFLAGS)  $(LIBMLX_FLAGS) $(LIBFT_FLAGS) -L $(LIBMLX_DIR) -L $(LIBFT_DIR) -o $(NAME) -no-pie

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all