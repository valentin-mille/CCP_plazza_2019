##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile Plazza
##

CFLAGS  =       -Wall -Wextra -W

SRC     =		main.cpp							\
				driver.cpp							\
				Parser/Parser.cpp					\
				Tools/Usage.cpp						\
				Exception/Exception.cpp				\
				Exception/ExceptionParser.cpp		\
				Exception/ExceptionPlazza.cpp		\
				Reception/Reception.cpp				\

OBJ     =       $(SRC:.cpp=.o)

NAME    =       plazza

all:    $(NAME)

$(NAME):        $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAGS)

debug: fclean $(OBJ)
	gcc -ggdb -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

auteur:
	echo $(USER) > auteur

.PHONY: all clean fclean re