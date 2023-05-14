# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 02:42:54 by absalhi           #+#    #+#              #
#    Updated: 2023/05/14 18:07:24 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libmlx.a

SRCS		=	mlx_shaders.c		mlx_new_window.m	mlx_init_loop.m		\
				mlx_new_image.m		mlx_xpm.c			mlx_int_str_to_wordtab.c
SRCS		+=	mlx_png.c			mlx_mouse.m

_OBJS		=	$(SRCS:.c=.o)
OBJS		=	$(_OBJS:.m=.o)

CFLAGS		=	-DSTRINGPUTX11 -Wno-deprecated-declarations -O2

NONE		=	'\033[0m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'

.c.o		:
				@echo $(ITALIC)$(GRAY) "     - Making mlx/$<..." $(NONE)
				@cc $(CFLAGS) -c $< -o $(<:.c=.o)
.m.o		:
				@echo $(ITALIC)$(GRAY) "     - Making mlx/$<..." $(NONE)
				@cc $(CFLAGS) -c $< -o $(<:.m=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				@echo $(ITALIC)$(GRAY) "     - Compiling library $(NAME)..." $(NONE)
				@ar rcs $(NAME) $(OBJS)

clean		:
				@echo $(ITALIC)$(GRAY) "     - Removing mlx object files..." $(NONE)
				@rm -rf $(OBJS) *~

fclean		:	clean
				@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
				@rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
