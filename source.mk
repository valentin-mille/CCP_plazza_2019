##
## EPITECH PROJECT, 2019
## source.mk
## File description:
## source for file
##

CC			=		g++

LD			=		$(CC)

CXXFLAGS  	=       -Wall -Wextra -W -std=c++17		\

FLAGS		=		Tools/							\
					Reception/ 						\
					Launcher/ 						\
					Parser/ 						\
					Exception/ 						\
					Pizza/							\
					IPC/							\
					Cooks/ 							\
					Kitchens/ 						\
					Ingredients/ 					\
					Clock/ 							\


SRC     	=		main.cpp											\
					driver.cpp											\
					src/Clock/clock.cpp 								\
					src/Parser/Parser.cpp								\
					src/Tools/Usage.cpp									\
					src/Tools/ParseCommandLine.cpp 						\
					src/Tools/CleanOrder.cpp							\
					src/Tools/getCountPizza.cpp							\
					src/Tools/tokeniseString.cpp						\
					src/Exception/Exception.cpp							\
					src/Exception/ExceptionParser.cpp					\
					src/Exception/ExceptionPlazza.cpp					\
					src/Reception/Reception.cpp							\
					src/IPC/InterProcessCom.cpp							\
					src/IPC/Operators.cpp								\
					src/Kitchens/Kitchens.cpp 							\
					src/Pizza/APizza.cpp 								\
					src/Cooks/Cooks.cpp									\

TEST 		=		testsParseCommandLine.cpp 							\

SRC_TEST	=		$(addprefix ../, $(filter-out main.cpp, $(SRC)))	\
					$(addprefix src/, $(TEST))
