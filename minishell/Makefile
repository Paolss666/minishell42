# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 13:55:48 by npaolett          #+#    #+#              #
#    Updated: 2023/11/17 14:34:13 by npaolett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

RM = rm -fr

CFLAGS = -g3 -Wall -Wextra -Werror 

INCL = -I -I./libft 

SRC =	src/build/ft_pwd.c \
		src/parsing/parsing_commandes.c 

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