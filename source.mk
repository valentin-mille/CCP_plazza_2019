##
## EPITECH PROJECT, 2019
## source.mk
## File description:
## source for file
##

CC			=		g++

LD			=		$(CC)

CXXFLAGS  	=       -Wall -Wextra -W -std=c++17 -pthread -I include -I./src -I./src/clock -I./src/threadpool -I./src/cook -I./src/ingredient -I./src/kitchen -I ./src/pizza

FLAGS		=		Tools/							\
					Reception/ 						\
					Launcher/ 						\
					Parser/ 						\
					Exception/ 						\
					IPC/							\
					Cooks/ 							\
					pizza/							\
					kitchens/ 						\
					Ingredients/ 					\
					Clock/ 							\
					Process/						\


SRC     	=		main.cpp											\
					driver.cpp											\
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
					src/Process/Process.cpp								\
					src/clock/clock.cpp\
					src/cook/Cook.cpp\
					src/kitchen/Kitchen.cpp\
					src/pizza/APizza.cpp\
					src/pizza/Regina.cpp\
					src/threadpool/ThreadPool.cpp\

TEST 		=		testsParseCommandLine.cpp 							\

SRC_TEST	=		$(addprefix ../, $(filter-out main.cpp, $(SRC)))	\
					$(addprefix src/, $(TEST))
