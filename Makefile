##
## EPITECH PROJECT, 2019
## JAM_streeart_2019
## File description:
## Makefile
##

include source.mk

GCV 		= 	gcovr
GCVNAME 	= 	coverage.html
GCVFLAGS 	= 	--html-details --html
GCVEXCLUDE 	= 	--exclude tests/ --exclude gcovr/

OBJ		=	$(addprefix ./src/, $(SRC:.cpp=.o))

NAME		=	plazza

CPPFLAGS 	=	$(addprefix -I./src/, $(FLAGS))

$(NAME): $(OBJ)
	@echo -e "\e[36;1m\nMAKE $(NAME)\n\e[0m"
	@$(LD) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

all:$(NAME)

tests_run:
	@make tests_run -C tests/ --no-print-directory
	@$(GCV) $(GCVEXCLUDE)
	@$(GCV) -r ./ $(GCVFLAGS) -o $(GCVNAME) $(GCVEXCLUDE)

clean:
	@echo -e "\e[31;1mCLEANING OBJ: $(NAME)\e[0m"
	@make clean -C tests/ --no-print-directory
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then                         \
		        printf "[\033[31;1m\xe2\x9c\x98\033[0m] $(var)\n"        \
		        && rm -rf $(var) ; fi ;)
	@rm -rf $(OBJ)

fclean: clean
	@echo -e "\033[31;1mCLEANING: $(NAME)\033[0m"
	@make fclean -C tests/ --no-print-directory
	@if [ -e $(NAME) ] ; then                                               \
		        printf "[\033[31;1m\xe2\x9c\x98\033[0m] $(NAME)\n"       \
		        && rm -f $(NAME) ; fi
	@rm -f $(NAME) $(NAME_TESTS)
	@rm -f *.html

re:	fclean	all

%.o:            %.cpp
		@echo -e "[\033[32;1m\xe2\x9c\x93\033[0m] $<$(END) \033[31;1m\xe2\x9f\xb6\033[0m $@"
		@$(LD) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY:	all	clean debug tests_run fclean re $(NAME)
