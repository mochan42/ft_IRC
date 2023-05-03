# **************************************************************************** #
# VARIABLES

NAME				:= ircserv	

CC					:= c++
CFLAGS				:= -Wall -Wextra -Werror -std=c++98 -lm -g
RM					:= rm -rf
INCS				:= -I ./inc/
SRC_DIR				:= ./src/
OBJ_DIR				:= ./obj/

# **************************************************************************** #
# COLORS

GREEN				:= \033[0;92m
YELLOW				:= \033[0;93m
BLUE				:= \033[0;94m
END_COLOR			:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC_FILES			:= Server.cpp main.cpp User.cpp Message.cpp Channel.cpp replyLib.cpp Utils.cpp \

BOT_SRC_FILES		:= Bot.cpp startBot.cpp

OBJ_FILES			:= ${SRC_FILES:.cpp=.o}
BOT_OBJ_FILES		:= ${BOT_SRC_FILES:.cpp=.o}

SRC					:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ					:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

BOT_SRC				:= $(addprefix $(SRC_DIR), $(BOT_SRC_FILES))
BOT_OBJ				:= $(addprefix $(OBJ_DIR), $(BOT_OBJ_FILES))

# **************************************************************************** #
# RULES

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
# only the program here is checked against the flags

debug: CFLAGS += -DDEBUG -g
debug: fclean all

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
# This rule is important to make sure that each object file is checked against the flags;
# -c	:	gcc option to compile each .c file into .o file.
# $<	:	represents the first prerequisite of the rule (each .c file 
#			contained in the src folder).
# -o	:	gcc option to define the name of the program (output) file :
#			"push_swap".
# $@	:	represents the filename of the target of the rule, i.e. each output
#			file which will be linked with the header file.

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

ircbot: $(OBJ_DIR) $(BOT_OBJ)
	$(CC) $(CFLAGS) $(INCS) $(BOT_OBJ) -o $@
	@echo "$(GREEN)ircbot compiled :)$(END_COLOR)"

clean:
	$(RM) $(OBJ) $(BOT_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ircbot
	$(RM) $(OBJ_DIR)

re: fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY: debug all clean fclean re