##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile Plazza
##

include source.mk

GCV 		= 	gcovr
GCVNAME 	= 	coverage.html
GCVFLAGS 	= 	--html-details --html -o coverage.html
GCVEXCLUDE 	= 	--exclude tests/ --exclude gcovr/

CPPFLAGS	=		$(addprefix -I, $(FLAGS))

OBJ     	=       $(SRC:.cpp=.o)

NAME    	=       plazza

all:    $(NAME)

$(NAME):        $(OBJ)
	$(LD) -o $(NAME) $(OBJ)
	@echo -e "\033[1;31mCOMPILATION: $(NAME)\033[0m"

tests_run:
	@make tests_run -C tests/ --no-print-directory
	@$(GCV) $(GCVEXCLUDE)
	@$(GCV) -r ./ $(GCVFLAGS) -o $(GCVNAME) $(GCVEXCLUDE)

debug: fclean $(OBJ)
	$(LD) -ggdb -o $(NAME) $(SRC)
	@echo -e "\033[1;31mDEBUGGING: $(NAME)\033[0m"

clean:
	@rm -f $(OBJ)
	@echo -e "\033[1;31mCLEAN: OBJ\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo -e "\033[1;31mFULL CLEAN: $(NAME)\033[0m"

re:	fclean all

author:
	echo $(USER) > auteur

.PHONY: all clean fclean re author debug
