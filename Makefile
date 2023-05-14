# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 21:24:26 by absalhi           #+#    #+#              #
#    Updated: 2023/05/14 19:47:07 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CFLAGS		=	-Wall -Wextra -Werror -Iincludes -Ilibft -Imlx
MXFLAGS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit
CC			=	cc
RM			=	rm -rf

NONE		=	'\033[0m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'

_LIBCUB		=	cub_occurences.c cub_line.c cub_file.c cub_time.c
LIBCUB		=	$(addprefix libcub/, $(_LIBCUB))

_UTILS		=	cub_errors.c cub_free.c cub_keys.c cub_pixel_put.c cub_scale_img.c
UTILS		=	$(addprefix utils/, $(_UTILS))

_PARSING	=	cub_parser.c cub_file_parser.c cub_file_checker.c		\
				cub_file_line.c cub_map.c cub_check.c cub_map_norm.c
PARSING		=	$(addprefix parsing/, $(_PARSING))

_SPRITES	=	weapon.c sprite_renderer.c
SPRITES	=	$(addprefix rendering/sprites/, $(_SPRITES))

_RENDERING	=	cub_render.c cub_init.c
RENDERING	=	$(addprefix rendering/, $(_RENDERING)) $(TEXTURES) $(SPRITES)

_SRCS		=	$(LIBCUB) $(UTILS) $(PARSING) $(RENDERING)
SRCS		=	$(addprefix srcs/, $(_SRCS)) main.c
OBJS		=	$(SRCS:.c=.o)

.c.o		:
				@echo $(ITALIC)$(GRAY) "     - Making $<..." $(NONE)
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				@make -C libft/
				@make -C mlx/
				@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
				@$(CC) $(CFLAGS) $(MXFLAGS) -Llibft -lft $(OBJS) -o $(NAME)
				@echo $(GREEN)"- Compiled -"$(NONE)

debug		:	CFLAGS += -D DEBUG
debug		:	re

minimap		:	CFLAGS += -D MINIMAP
minimap		:	re

no_textures	:	CFLAGS += -D NO_TEXTURES
no_textures	:	re

clean		:
				@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
				@$(RM) $(OBJS)
				@make clean -C libft/
				@make clean -C mlx/

fclean		:	clean
				@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
				@$(RM) $(NAME)
				@make fclean -C libft/
				@make fclean -C mlx/

re			:	fclean all

norm		:
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking header files norminette..." $(GRAY)
				@norminette includes/
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking source files norminette..." $(GRAY)
				@norminette $(SRCS)

.PHONY		:	all debug clean fclean re norm
