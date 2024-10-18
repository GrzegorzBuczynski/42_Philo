


all:
	rm -f philo
	gcc philo.c -g -o philo -lpthread

clean:
	rm -f philo

fclean: clean	

re: fclean all

.PHONY: all clean fclean re bonus

push:
	git add .
	git commit -m "make push!"
	git push