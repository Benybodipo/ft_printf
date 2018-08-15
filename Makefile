# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besteba <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/09 10:21:42 by besteba           #+#    #+#              #
#    Updated: 2018/07/09 10:21:43 by besteba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a
SRC = *.c
CC = gcc
OBJ = *.o
FLAGS =  -Wall -Wextra -Werror -I
ARC = ar rc

$(NAME):
	@$(CC) $(FLAGS) -c $(SRC)
	@$(ARC) $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm $(NAME)

re: fclean all
