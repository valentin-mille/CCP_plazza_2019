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

CPPFLAGS	=	$(addprefix -Isrc/, $(FLAGS))

OBJ     	=   $(SRC:.cpp=.o)

NAME		=	plazza

$(NAME): $(OBJ)
	@echo -e "\e[36;1m\nMAKE $(NAME)\n\e[0m"
	$(LD) -o $(NAME) $(OBJ)
	#@$(LD) $^ -o $@ $(CXXFLAGS) $(CPPFLAGS)

all:$(NAME)

debug: fclean $(OBJ)
	$(LD) -ggdb -o $(NAME) $(SRC)
	@echo -e "\033[1;32mDEBUGGING: $(NAME)\033[0m"

tests_run:
	@make tests_run -C tests/ --no-print-directory
	@$(GCV) $(GCVEXCLUDE)
	@$(GCV) -r ./ $(GCVFLAGS) -o $(GCVNAME) $(GCVEXCLUDE)

clean:
	@echo -e "\e[31;1mCLEANING OBJ: $(NAME)\e[0m"
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then                      \
		        printf "[\033[31;1m\xe2\x9c\x98\033[0m] $(var)\n"        \
		        && rm -rf $(var) ; fi ;)
	@make clean -C tests/ --no-print-directory
	@rm -rf $(OBJ)

fclean: clean
	@echo -e "\033[31;1mCLEANING: $(NAME)\033[0m"
	@make fclean -C tests/ --no-print-directory
	@if [ -e $(NAME) ] ; then                                            \
		        printf "[\033[31;1m\xe2\x9c\x98\033[0m] $(NAME)\n"       \
		        && rm -f $(NAME) ; fi
	@rm -f $(NAME) $(NAME_TESTS)
	@rm -f *.html

re:	fclean	all

#%.o:            %.cpp
#		@echo -e "[\033[32;1m\xe2\x9c\x93\033[0m] $<$(END) \033[31;1m\xe2\x9f\xb6\033[0m $@"
#		@$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY:	all	clean debug tests_run fclean re $(NAME)
