##
## EPITECH PROJECT, 2019
## source.mk
## File description:
## source for file
##

CXX			=		g++

LD			=		$(CXX)

CXXFLAGS  	=		-Wall -Wextra -W -std=c++17

LDLIBS 		=		-lpthread

FLAGS		=		Tools/							\
					Reception/ 						\
					Launcher/ 						\
					Parser/ 						\
					Exception/ 						\
					IPC/							\
					Process/						\
					cook/ 							\
					kitchen/ 						\
					pizza/ 							\
					clock/							\
					ingredient/ 					\
					threadpool/						\


SRC     	=		main.cpp										\
					driver.cpp										\
					Parser/Parser.cpp								\
					Tools/Usage.cpp									\
					Tools/ParseCommandLine.cpp 						\
					Tools/CleanOrder.cpp							\
					Tools/getCountPizza.cpp							\
					Tools/tokeniseString.cpp						\
					Exception/Exception.cpp							\
					Exception/ExceptionParser.cpp					\
					Exception/ExceptionPlazza.cpp					\
					Reception/Reception.cpp							\
					IPC/InterProcessCom.cpp							\
					IPC/Operators.cpp								\
					Process/Process.cpp								\
					clock/clock.cpp									\
					cook/Cook.cpp									\
					kitchen/Kitchen.cpp								\
					pizza/APizza.cpp								\
					pizza/Regina.cpp								\
					threadpool/ThreadPool.cpp						\

TEST 		=		testsParseCommandLine.cpp 						\

SRC_TEST	=		$(addprefix ../src/, $(filter-out main.cpp, $(SRC)))	\
					$(addprefix src/, $(TEST))
