# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 09:55:57 by cudoh             #+#    #+#              #
#    Updated: 2023/04/21 11:34:19 by fsemke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS:= main.cpp 
DIR_SRCS_TEST = ./src/
DIR_OBJS_TEST = ./obj/
DIR_SRCS_PROJ = ../src/
DIR_OBJS_PROJ = ../obj/

#SRC_FILES	:= $(shell ls ./src | xargs)
SRC_FILES_TEST	:=	main.cpp test_channel.cpp \
#				main_user.cpp 

# PROJECT FILES TO BE TESTED ARE LISTE HERE 
SRC_FILES_PROJ	:= Channel.cpp User.cpp

# PROJECT FILES TO BE TESTED ARE LISTE HERE 
SRC_FILES_PROJ	:= Server.cpp User.cpp



OBJ_FILES_TEST	:=	$(SRC_FILES_TEST:.cpp=.o)	# Test object files
OBJ_FILES_PROJ	:=	$(SRC_FILES_PROJ:.cpp=.o)	# Project object files

SRCS_TEST		:=	$(addprefix $(DIR_SRCS_TEST), $(SRC_FILES_TEST))
OBJS_TEST		:=	$(addprefix $(DIR_OBJS_TEST), $(OBJ_FILES_TEST))

SRCS_PROJ		:=	$(addprefix $(DIR_SRCS_PROJ), $(SRC_FILES_PROJ))
OBJS_PROJ		:=	$(addprefix $(DIR_OBJS_PROJ), $(OBJ_FILES_PROJ))


OBJ_FILES_TEST	:=	$(SRC_FILES_TEST:.cpp=.o)	# Test object files
OBJ_FILES_PROJ	:=	$(SRC_FILES_PROJ:.cpp=.o)	# Project object files

SRCS_TEST		:=	$(addprefix $(DIR_SRCS_TEST), $(SRC_FILES_TEST))
OBJS_TEST		:=	$(addprefix $(DIR_OBJS_TEST), $(OBJ_FILES_TEST))

SRCS_PROJ		:=	$(addprefix $(DIR_SRCS_PROJ), $(SRC_FILES_PROJ))
OBJS_PROJ		:=	$(addprefix $(DIR_OBJS_PROJ), $(OBJ_FILES_PROJ))

NAME = test

CC = g++
STD_CPP = c++14
CFLAGS = -Werror -Wall -Wextra -g -std=$(STD_CPP)
INCLUDES = -I ./inc -I ../inc

NAME : all
all : $(NAME)
$(NAME) : $(OBJS_TEST) $(OBJS_PROJ)
	@echo "\033[1;33mCompiling Executables: $(NAME) \033[0m"
	$(CC) $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo; echo "\033[1;32mCompilation Successful. \033[0m"
	@echo; echo

	
# Compile *.o files for Test
#%.o : %.cpp
$(DIR_OBJS_TEST)%.o : $(DIR_SRCS_TEST)%.cpp
	@echo
	@mkdir -p $(dir $@)
	@echo "\033[1;33mCompiling OBJ files \033[0m"
	$(CC) -c $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo


# Compile *.o files for Project
$(DIR_OBJS_PROJ)%.o : $(DIR_SRCS_PROJ)%.cpp
	@echo
	@mkdir -p $(dir $@)
	@echo "\033[1;33mCompiling OBJ files \033[0m"
	$(CC) -c $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo
	
	
# remove all object files
fclean:
	rm -rf $(DIR_OBJS_TEST)
	rm -rf $(DIR_OBJS_PROJ)
#	rm -rf *.o

# remove final target files
clean: fclean
	rm -rf $(NAME)

# recompile everything
re: clean all

.PHONY : all fclean clean re 
