# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 17:18:06 by gbuczyns          #+#    #+#              #
#    Updated: 2024/11/05 17:21:24 by gbuczyns         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
WARNFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
RLFLAG = -lreadline -lm -g
CFLAGS = -g


# Object directory
OBJ_DIR = obj/

# Source files
SRCS =	init.c \
		main.c \
		monitor.c \
		philo.c \
		rutine.c \
		utils_2.c \
		utils.c \
		validate.c 		


OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)
	
$(NAME): $(OBJS)
	@echo "Linking objects into executable..."
	$(CC) $(WARNFLAGS) $(CFLAGS)  $(OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

push:
	git add .
	git commit -m "make push!"
	git push

#% valgrind --tool=helgrind ./philo 5 800 200 200 7