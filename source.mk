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
					Pizza/							\
					IPC/							\
					Cooks/ 							\
					Kitchens/ 						\


SRC     	=		main.cpp												\
					driver.cpp												\
					sources/Parser/Parser.cpp								\
					sources/Tools/Usage.cpp									\
					sources/Tools/ParseCommandLine.cpp 						\
					sources/Exception/Exception.cpp							\
					sources/Exception/ExceptionParser.cpp					\
					sources/Exception/ExceptionPlazza.cpp					\
					sources/Reception/Reception.cpp							\
					sources/Pizza/Pizza.cpp 								\
					sources/IPC/InterProcessCom.cpp							\
					sources/Kitchens/Kitchens.cpp 							\
					sources/Cooks/Cooks.cpp									\

TEST 		=		testsParseCommandLine.cpp 								\

SRC_TEST	=		$(addprefix ../, $(filter-out main.cpp, $(SRC)))		\
					$(addprefix sources/, $(TEST))
