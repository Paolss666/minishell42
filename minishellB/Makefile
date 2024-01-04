# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 16:22:18 by npaolett          #+#    #+#              #
#    Updated: 2024/01/04 16:23:27 by npaolett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc

RM = rm -fr

CFLAGS = -g3 -Wall -Wextra -Werror 

INCL = -I -I./libft 

SRC =	src/build/ft_pwd.c\
		src/build/env/ft_env.c \
		src/build/echo/ft_echo.c \
		src/build/ft_exit.c  \
		src/build/cd/ft_cd.c 	  \
		src/build/export/ft_export.c  \
		src/build/ft_unset.c    \
		src/execve/ft_exceve.c	 \
		src/parsing/parsing_commandes.c \
		src/error_manager/error_manager.c \
		src/error_manager/ft_error_case_1.c \
		src/error_manager/ft_error_blank.c    \
		src/error_manager/ft_error_shift_operator.c\
		src/error_manager/ft_error_directory.c \
		src/error_manager/ft_error_pipe.c		\
		src/error_manager/epur_str.c			\
		src/error_manager/ft_error_operand.c	\
		src/error_manager/ft_count_sign.c		\
		src/error_manager/ft_error_parenthesis.c\
		src/error_manager/ft_error_semicol.c \
		src/error_manager/ft_error_stx.c   \
		src/pipe/error.c \
		src/pipe/ft_pipe.c \
		src/pipe/init_list.c\
		src/pipe/pipe_utils.c \

OBJ = $(SRC:.c=.o)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)


LIBFT = ./libft/libft.a


$(NAME): $(OBJ)
	make lib
	cc -o $(NAME) $(OBJ) $(LIBFT) -lreadline 

# $(BONUS): $(OBJ_BONUS)
	# make lib
	# cc -o $(BONUS) $(OBJ_BONUS) $(LIBFT) 

all : $(NAME)

bonus : $(BONUS)

%.o: %.c
	cc $(INCL) $(CFLAGS) -o $@ -c $<


lib:
	make -C ./libft/ all
	
clean:
	@make -C libft/ clean
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(LIBFT)  $(BONUS)

re: fclean 
	make all

rebonus: fclean
		make bonus 

.PHONY: all clean fclean re