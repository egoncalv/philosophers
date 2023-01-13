# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:24:24 by egoncalv          #+#    #+#              #
#    Updated: 2023/01/13 14:46:42 by egoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

THREAD = -pthread

NAME = philo

SRC = 	main.c \
		utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(THREAD) $(OBJ) -o $(NAME)
	@echo "Philosophers Compiled"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ)
	
fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)

.phony: all clean fclean re bonus
