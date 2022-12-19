# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/14 21:25:07 by dkocob        #+#    #+#                  #
#    Updated: 2022/12/19 15:10:39 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:
SRC			= main.c libft.c init.c end.c threads.c actions.c death.c
OBJ			= $(SRC:.c=.o)
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror -pthread -o3 #-g3 #-fsanitize=thread #-fsanitize=address 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
# number of philo time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] *
run:		$(NAME)
			./$(NAME) 200 410 200 200 2
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
