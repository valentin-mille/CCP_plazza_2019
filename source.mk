##
## EPITECH PROJECT, 2019
## source.mk
## File description:
## source for file
##

CC			=		g++

LD			=		$(CC)

CXXFLAGS  	=       -Wall -Wextra -W -std=c++14		\

FLAGS		=		Tools/							\
					Reception/ 						\
					Launcher/ 						\
					Parser/ 						\
					Exception/ 						\

SRC     	=		main.cpp												\
					driver.cpp												\
					Parser/Parser.cpp										\
					Tools/Usage.cpp											\
					Tools/ParseCommandLine.cpp 								\
					Exception/Exception.cpp									\
					Exception/ExceptionParser.cpp							\
					Exception/ExceptionPlazza.cpp							\
					Reception/Reception.cpp									\

TEST 		=		testsParseCommandLine.cpp 								\

SRC_TEST	=		$(addprefix ../, $(filter-out main.cpp, $(SRC)))		\
					$(addprefix sources/, $(TEST))
