# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/09 18:49:54 by dkocob        #+#    #+#                  #
#    Updated: 2022/11/18 21:05:35 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:
SRC			= main.c ft_atoi.c
OBJ			= $(SRC:.c=.o)
NAME		= philo
CFLAGS		= -Wall -Wextra -g -pthread -fsanitize=address #-Werror 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:		$(NAME)
			./$(NAME) 1 40 1 1 10
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run