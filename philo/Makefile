# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/14 21:25:07 by dkocob        #+#    #+#                  #
#    Updated: 2022/12/14 21:25:09 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:
SRC			= main.c libft.c init.c end.c threads.c actions.c death.c
OBJ			= $(SRC:.c=.o)
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror -g3 -pthread #-fsanitize=thread #-fsanitize=address

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
# number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] *
run:		$(NAME)
			./$(NAME) 4 310 200 100
			
# ./$(NAME) 4 310 200 100 free fork
# philo 200 410 200 200 (run for at least a couple of sec)
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
