##
## EPITECH PROJECT, 2018
## MyScript
## File description:
## Makefile
##

CC	=	gcc

CFLAGS	+=	-W -Wall -Wextra

CFLAGS	+=	-I./includes

NAME	=	my_script

DIR	=	srcs/

SRCS	=	$(DIR)main.c		\
			$(DIR)my_script.c	\
			$(DIR)create_file.c	\
			$(DIR)init.c		\
			$(DIR)free.c

OBJS	=	$(SRCS:.c=.o)

%.o: %.c
		@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
		@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

EXEC:	$(NAME)

all: EXEC

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

clean:
		@rm $(OBJS)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean:	clean
		@rm $(NAME)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re:		fclean all

.PHONY:	all exec clean fclean re