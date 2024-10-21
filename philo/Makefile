# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra -Werror
RLFLAG = -lreadline -lm -g
CFLAGS = -g


# Object directory
OBJ_DIR = obj/

# Source files
SRCS =	error.c \
		philo.c \
		time.c \
		validate.c \
		dinner.c \
		write.c \
		init.c \
		safe_functions.c \
		getters_and_setters.c \
		utils.c


OBJS = $(SRCS:.c=.o)

# Program Name
NAME = philo



# Default rule
all: $(NAME)
	
#$(LIBFT) $(FTPRINTF) $(NAME)
$(NAME): $(OBJS)
#	clear
	@echo "Linking objects into executable..."
	$(CC) $(WARNFLAGS) $(CFLAGS)  $(OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) -c $< -o $@ 

# Clean up obj files
clean:
	rm -f $(OBJS)

# Full clean up
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re bonus

push:
	git add .
	git commit -m "make push!"
	git push
