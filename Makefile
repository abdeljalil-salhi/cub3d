# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 21:24:26 by absalhi           #+#    #+#              #
#    Updated: 2023/05/19 11:57:18 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
B_NAME		=	cub3D_bonus

CFLAGS		=	-Wall -Wextra -Werror -Ilibft -Imlx
MXFLAGS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit
CC			=	cc
RM			=	rm -rf

NONE		=	'\033[0m'
RED			=	'\033[0;31m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'

# -------------------------------- MANDATORY --------------------------------- #

_LIBCUB		=	cub_occurences.c cub_line.c cub_file.c cub_time.c cub_color.c
LIBCUB		=	$(addprefix libcub/, $(_LIBCUB))

_UTILS		=	cub_errors.c cub_free.c cub_keys.c cub_pixel_put.c 
UTILS		=	$(addprefix utils/, $(_UTILS))

_PARSING	=	cub_parser.c cub_file_parser.c cub_file_checker.c						\
				cub_file_line.c cub_map.c cub_check.c cub_map_norm.c
PARSING		=	$(addprefix parsing/, $(_PARSING))

_RENDERING	=	cub_render.c cub_init.c raycasting.c draw_walls.c player_movement.c
RENDERING	=	$(addprefix rendering/, $(_RENDERING))

_SRCS		=	$(LIBCUB) $(UTILS) $(PARSING) $(RENDERING)
SRCS		=	$(addprefix mandatory/srcs/, $(_SRCS)) mandatory/main.c
OBJS		=	$(SRCS:.c=.o)

# ----------------------------------- BONUS ---------------------------------- #

_BLIBCUB	=	count_occurences.c		line_utils.c	file_open.c			time.c
B_LIBCUB	=	$(addprefix libcub/, $(_BLIBCUB))

_BUTILS		=	errors.c		free_memory.c	image_scaling.c		keyboard_hooks.c	\
				mouse_hooks.c	pixel_put.c		sounds.c
B_UTILS		=	$(addprefix utils/, $(_BUTILS))

_BPARSING	=	parser.c 		object_setter.c											\
				file/parser.c	file/checker.c											\
				map/parser.c	map/checker.c	map/analyzer.c
B_PARSING	=	$(addprefix parsing/, $(_BPARSING))

_BSPRITES	=	weapon.c		medkit.c		door.c		tips.c
_BSINIT		=	$(addprefix init/,														\
				objects.c		enemy/soldier.c		enemy/cyberdemon.c		weapon.c	)
_BSENEMY	=	$(addprefix enemy/,														\
				enemy.c			state_checker.c		framer.c		movement.c			)
_BSRENDER	=	$(addprefix render/,													\
				renderer.c		sort.c				utils.c								)
B_SPRITES	=	$(addprefix sprites/, $(_BSPRITES) $(_BSINIT) $(_BSENEMY) $(_BSRENDER))

_BTEXTURES	=	init/init.c
_BITEXTURES	=	$(addprefix init/,														\
				hud.c			walls.c													)
B_TEXTURES	=	$(addprefix textures/, $(_BTEXTURES) $(_BITEXTURES))

_BRENDERING	=	render.c		init.c		movement_checker.c
B_RENDERING	=	$(addprefix rendering/, $(_BRENDERING) $(B_SPRITES) $(B_TEXTURES))

_BSRCS		=	$(B_LIBCUB) $(B_UTILS) $(B_PARSING) $(B_RENDERING)
B_SRCS		=	$(addprefix bonus/srcs/, $(_BSRCS)) bonus/main.c
B_OBJS		=	$(B_SRCS:.c=.o)

# ---------------------------------------------------------------------------- #

.c.o		:
				@echo $(ITALIC)$(GRAY) "     - Making $<..." $(NONE)
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all			:	$(NAME)

$(NAME)		:	CFLAGS += -Imandatory/includes
$(NAME)		:	$(OBJS)
				@make -C libft/
				@make -C mlx/
				@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
				@$(CC) $(CFLAGS) $(MXFLAGS) -Llibft -lft $(OBJS) -o $(NAME)
				@echo $(GREEN)"- Compiled -"$(NONE)

bonus		:	$(B_NAME)

$(B_NAME)	:	CFLAGS += -Ibonus/includes
$(B_NAME)	:	$(B_OBJS)
				@make -C libft/
				@make -C mlx/
				@echo $(ITALIC)$(GRAY) "     - Compiling $(B_NAME)..." $(NONE)
				@$(CC) $(CFLAGS) $(MXFLAGS) -Llibft -lft $(B_OBJS) -o $(B_NAME)

minimap		:	CFLAGS += -D MINIMAP
minimap		:	re

no_textures	:	CFLAGS += -D NO_TEXTURES
no_textures	:	re

help		:
				@printf "\n"
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Usage:" $(GRAY)
				@echo "     - ./"$(NAME)$(NONE)$(ITALIC)$(GREEN) "[map].cub" $(NONE)$(GRAY) "to run the game."
				@printf "\n"
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Available options:" $(NONE)$(GRAY)
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "all" $(NONE)$(GRAY) "to compile the project (mandatory part)."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "bonus" $(NONE)$(GRAY) "to compile the project (bonus part)."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "debug" $(NONE)$(GRAY) "to compile the project with debug flags."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "minimap" $(NONE)$(GRAY) "to compile the project with minimap."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "no_textures" $(NONE)$(GRAY) "to compile the project without textures."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "clean" $(NONE)$(GRAY) "to remove object files."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "fclean" $(NONE)$(GRAY) "to remove object files and $(NAME)."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "re" $(NONE)$(GRAY) "to recompile the project."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "norm" $(NONE)$(GRAY) "to check norminette."
				@echo "     - make" $(NONE)$(ITALIC)$(GREEN) "help" $(NONE)$(GRAY) "to show this help." $(NONE)
				@printf "\n"
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Map editing:" $(NONE)$(GRAY)
				@echo "     - [ "$(NONE)$(GREEN)"1"$(NONE)$(GRAY)" -> "$(NONE)$(GREEN)"5"$(NONE)$(GRAY)" ] Wall"
				@echo "     - [ "$(NONE)$(GREEN)"N"$(NONE)$(GRAY)" / "$(NONE)$(GREEN)"S"$(NONE)$(GRAY)" / "$(NONE)$(GREEN)"E"$(NONE)$(GRAY)" / "$(NONE)$(GREEN)"W"$(NONE)$(GRAY)" ] Player"
				@echo "     - [ "$(NONE)$(GREEN)"0"$(NONE)$(GRAY)" ] Empty space (floor)"
				@echo "     - [ "$(NONE)$(GREEN)"D"$(NONE)$(GRAY)" ] Door"
				@echo "     - [ "$(NONE)$(GREEN)"B"$(NONE)$(GRAY)" ] Barrel"
				@echo "     - [ "$(NONE)$(GREEN)"L"$(NONE)$(GRAY)" ] Lamp"
				@echo "     - [ "$(NONE)$(GREEN)"P"$(NONE)$(GRAY)" ] Pillar"
				@echo "     - [ "$(NONE)$(GREEN)"G"$(NONE)$(GRAY)" ] Green fire lamp"
				@echo "     - [ "$(NONE)$(GREEN)"M"$(NONE)$(GRAY)" ] Medkit"
				@echo "     - [ "$(NONE)$(GREEN)"V"$(NONE)$(GRAY)" ] Enemy - Soldier"
				@echo "     - [ "$(NONE)$(GREEN)"C"$(NONE)$(GRAY)" ] Enemy - Cyberdemon"

clean		:
				@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
				@$(RM) $(OBJS) $(B_OBJS)
				@make clean -C libft/
				@make clean -C mlx/

fclean		:	clean
				@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
				@$(RM) $(NAME) $(B_NAME)
				@make fclean -C libft/
				@make fclean -C mlx/

re			:	fclean all

re_bonus	:	fclean bonus

norm		:
				@echo $(NONE)$(ITALIC)$(RED) "    ~ Checking mandatory part"
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking header files norminette..." $(GRAY)
				@norminette mandatory/includes/
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking source files norminette..." $(GRAY)
				@norminette $(SRCS)
				@echo $(NONE)$(ITALIC)$(RED) "    ~ Checking bonus part"
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking header files norminette..." $(GRAY)
				@norminette bonus/includes/
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking source files norminette..." $(GRAY)
				@norminette $(B_SRCS)

.PHONY		:	all bonus minimap no_textures help clean fclean re re_bonus norm
