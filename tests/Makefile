##
## EPITECH PROJECT, 2019
## Makfile
## File description:
## Test makefile project
##

include ../source.mk

OBJ_TEST 			=		$(SRC_TEST:.cpp=.o)

NAME_TEST 			=		../unit_tests

CC					=		g++

$(LD)				=		$(CC)

CPPFLAGS			= 		$(addprefix -I../sources/, $(FLAGS))

LDFLAGS 			=		-lcriterion --coverage -lgcov

tests_run:	$(OBJ_TEST)
	@$(LD) -o $(NAME_TEST) $(OBJ_TEST) $(LDFLAGS)
	@echo -e "\033[1;32mRUN TEST: $(NAME_TEST)\033[0m"
	@./$(NAME_TEST)

all: tests_run

clean:
	@rm -rf $(OBJ_TEST) $(OBJ_TEST:.o=.gcda) $(OBJ_TEST:.o=.gcno)
	@echo -e "\033[1;32mCLEANING TEST: $(NAME_TEST)\033[0m"

fclean:	clean
	@rm -f $(NAME_TEST)
	@echo -e "\033[1;32mFULL CLEANING TEST: $(NAME_TEST)\033[0m"

.PHONY: all clean fclean tests_run
