##
## EPITECH PROJECT, 2019
## JAM_streeart_2019
## File description:
## Makefile
##

SRC			=	main.cpp				\
				clock/clock.cpp\
				cook/Cook.cpp\
				kitchen/Kitchen.cpp\
				pizza/APizza.cpp\
				pizza/Regina.cpp\
				threadpool/ThreadPool.cpp\

OBJ		=	$(addprefix ./src/, $(SRC:.cpp=.o))

NAME		=	plazza

override CXXFLAGS	+= -ggdb3 -Wall -pthread -Wextra -I./src -I./src/clock -I./src/threadpool -I./src/cook -I./src/ingredient -I./src/kitchen -I ./src/pizza -std=c++17

$(NAME): $(OBJ)
	@echo -e "\e[36;1m\nMAKE $(NAME)\n\e[0m"
	@$(CXX) $^ -o $@ $(CXXFLAGS)

all:$(NAME)

clean:
	@echo -e "\e[31;1mCLEANING OBJ: $(NAME)\e[0m"
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then                         \
		        printf "[\033[31;1m\xe2\x9c\x98\033[0m] $(var)\n"        \
		        && rm -rf $(var) ; fi ;)
	@rm -rf $(OBJ)

fclean: clean
	@echo -e "\033[31;1mCLEANING: $(NAME)\033[0m"
	@if [ -e $(NAME) ] ; then                                               \
		        printf "[\033[31;1m\xe2\x9c\x98\033[0m] $(NAME)\n"       \
		        && rm -f $(NAME) ; fi
	@rm -f $(NAME) $(NAME_TESTS)

re:	fclean	all

%.o:            %.cpp
		@echo -e "[\033[32;1m\xe2\x9c\x93\033[0m] $<$(END) \033[31;1m\xe2\x9f\xb6\033[0m $@"
		@$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY:	all	clean	fclean	re
