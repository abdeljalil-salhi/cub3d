# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 21:24:26 by absalhi           #+#    #+#              #
#    Updated: 2023/03/20 00:16:21 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CFLAGS		=	-Wall -Wextra -Werror -Iincludes -Ilibft
MXFLAGS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit
CC			=	cc
RM			=	rm -rf

NONE		=	'\033[0m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'

_LIBCUB		=	cub_occurences.c
LIBCUB		=	$(addprefix libcub/, $(_LIBCUB))

_UTILS		=	cub_errors.c	cub_free.c
UTILS		=	$(addprefix utils/, $(_UTILS))

_PARSING	=	cub_parser.c	cub_file_parser.c
PARSING		=	$(addprefix parsing/, $(_PARSING))

_SRCS		=	$(LIBCUB) $(UTILS) $(PARSING)
SRCS		=	$(addprefix srcs/, $(_SRCS)) main.c
OBJS		=	$(SRCS:.c=.o)

.c.o		:
				@echo $(ITALIC)$(GRAY) "     - Making $<..." $(NONE)
				@$(CC) $(CFLAGS) -Imlx -c $< -o $(<:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
				@make -C libft/
				@$(CC) $(CFLAGS) $(MXFLAGS) -L libft/ -lft $(OBJS) -o $(NAME)
				@echo $(GREEN)"- Compiled -"$(NONE)

clean		:
				@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
				@$(RM) $(OBJS)
				@make clean -C libft/

fclean		:	clean
				@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
				@$(RM) $(NAME)
				@make fclean -C libft/

re			:	fclean all

norm		:
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking header files norminette..." $(GRAY)
				@norminette includes/
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking source files norminette..." $(GRAY)
				@norminette $(SRCS)

.PHONY		:	all clean fclean re norm
