# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 09:55:57 by cudoh             #+#    #+#              #
#    Updated: 2023/04/17 23:03:25 by pmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS:= main.cpp 
DIR_SRCS = ./src/
DIR_OBJS = ./obj/

SRC_FILES	:= $(shell ls ./src | xargs)
OBJ_FILES	:= $(SRC_FILES:.cpp=.o)

SRCS		:= $(addprefix $(DIR_SRCS), $(SRC_FILES))
OBJS		:= $(addprefix $(DIR_OBJS), $(OBJ_FILES))


NAME = test

CC = c++
STD_CPP = c++14
CFLAGS = -Werror -Wall -Wextra -g -std=$(STD_CPP)
INCLUDES = -I ./inc

NAME : all
all : $(NAME)
$(NAME) : $(OBJS) 
	@echo "\033[1;33mCompiling Executables: $(NAME) \033[0m"
	$(CC) $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo; echo "\033[1;32mCompilation Successful. \033[0m"
	@echo; echo

	
# obj files output
#%.o : %.cpp
$(DIR_OBJS)%.o : $(DIR_SRCS)%.cpp
	@echo
	@mkdir -p $(dir $@)
	@echo "\033[1;33mCompiling OBJ files \033[0m"
	$(CC) -c $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo


# remove all object files
fclean:
	rm -rf $(DIR_OBJS)
#	rm -rf *.o

# remove final target files
clean: fclean
	rm -rf $(NAME)

# recompile everything
re: clean all

.PHONY : all fclean clean re 