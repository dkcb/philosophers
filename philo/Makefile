# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/09 18:49:54 by dkocob        #+#    #+#                  #
#    Updated: 2022/12/13 18:26:55 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:
SRC			= main.c libft.c init.c end.c threads.c actions.c
OBJ			= $(SRC:.c=.o)
NAME		= philo
CFLAGS		= -Wall -Wextra -g3 -pthread -fsanitize=thread # -fsanitize=address #-Werror -fsanitize=address 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
# number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] *
run:		$(NAME)
			./$(NAME) 2 400 200 100
			
# ./$(NAME) 4 310 200 100 free fork
# philo 200 410 200 200 (run for at least a couple of sec)
# ./philo 4 310 200 100
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
