# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdagmer <kdagmer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 19:40:56 by kdagmer           #+#    #+#              #
#    Updated: 2019/12/27 12:57:47 by kdagmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= fillit

CC		= gcc $(CCFLAGS)

CCFLAGS	= -Wall -Wextra -Werror

SRCS 	= fillit.c error.c check.c keep.c tet_create.c

OBJECTS	= $(subst .c,.o,$(SRCS))

.PHONY: clean fclean all re lib

all: $(NAME)

$(NAME): lib $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) -L libft -l ft

$(OBJECTS):
	$(CC) -c $(SRCS) -I includes/ -I libft/

.PHONY: lclean run test

test: $(NAME) clean lclean run
	#make test

run:
	./$(NAME) valid.fillit

lclean:
	make -C libft fclean

lib:
	@make -C libft

clean:
	@rm -rf $(OBJECTS)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all