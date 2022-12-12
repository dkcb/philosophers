# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkocob <dkocob@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/09 18:49:54 by dkocob        #+#    #+#                  #
#    Updated: 2022/12/12 20:52:07 by dkocob        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH		= ./obj:./src:./inc/libft:
SRC			= main.c ft_atoi.c ft_strlen.c ft_putnbr_fd.c ft_putstr_fd.c
OBJ			= $(SRC:.c=.o)
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror #-g3 -pthread  -fsanitize=address #-fsanitize=thread#-Werror -fsanitize=address 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
# number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] *
run:		$(NAME)
			./$(NAME) 2 310 200 100
			
# ./$(NAME) 4 310 200 100 free fork
# philo 200 410 200 200 (run for at least a couple of sec)
# ./philo 4 310 200 100
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus run
