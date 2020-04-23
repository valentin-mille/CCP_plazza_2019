##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile Plazza
##

include source.mk

GCV 		= 	gcovr
GCVNAME 	= 	coverage.html
GCVFLAGS 	= 	--html-details --html
GCVEXCLUDE 	= 	--exclude tests/ --exclude gcovr/

CPPFLAGS	=		$(addprefix -Isources/, $(FLAGS))

OBJ     	=       $(SRC:.cpp=.o)

NAME    	=       plazza

all:    $(NAME)

$(NAME):        $(OBJ)
	$(LD) -o $(NAME) $(OBJ)
	@echo -e "\033[1;32mCOMPILATION: $(NAME)\033[0m"

tests_run:
	@make tests_run -C tests/ --no-print-directory
	@$(GCV) $(GCVEXCLUDE)
	@$(GCV) -r ./ $(GCVFLAGS) -o $(GCVNAME) $(GCVEXCLUDE)

debug: fclean $(OBJ)
	$(LD) -ggdb -o $(NAME) $(SRC)
	@echo -e "\033[1;32mDEBUGGING: $(NAME)\033[0m"

clean:
	@make clean -C tests/ --no-print-directory
	@rm -f $(OBJ)
	@rm -f *.html
	@echo -e "\033[1;32mCLEAN: OBJ\033[0m"

fclean: clean
	@make fclean -C tests/ --no-print-directory
	@rm -f $(NAME)
	@echo -e "\033[1;32mFULL CLEAN: $(NAME)\033[0m"

re:	fclean all

author:
	echo $(USER) > auteur

.PHONY: all clean fclean re author debug
