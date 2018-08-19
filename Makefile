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

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

INC = -I includes/

UTILS = ft_atoi.c ft_itoa_base.c ft_strcmp.c ft_strdup.c ft_strlen.c \
				ft_uitoa_base.c is_digit.c is_in_str.c preppend.c\

CORE =	add_zero.c ft_printf.c handle_format.c handle_length.c \
				handle_padding.c handle_pointers.c handle_precision.c handle_prefix.c \
				handle_printing.c handle_struct.c handle_wchart.c wchart_len.c \

COMP = $(addprefix core/, $(CORE)) $(addprefix utils/, $(UTILS))

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(COMP) #$(INC)
	@ar rc $(NAME) *.o
	@ranlib $(NAME)

clean:
		@rm -fr *.o

fclean: clean
		@rm -fr *.a

re: fclean all

.PHONY: all clean fclean
