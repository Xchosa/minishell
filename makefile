
NAME := minishell
CC := cc

#---------linux---------
CFLAGS	= -Wall -Wextra -Werror -g -I inc/ -ldl -lglfw -pthread -lm
#----------mac ---------
CFLAGS		= -Wall -Wextra -Werror -g -I inc/

LIBFT := ./libft/libft.a



SOURCE_DIR = ./src
GARBAGE_DIR := ./src/garbage_collector
PARSE_DIR = ./src/parser
EXECUTER_DIR = ./src/executer
INC_DIR = inc
OBJ_DIR = obj

VPATH = $(SOURCE_DIR):$(PARSE_DIR):$(EXECUTER_DIR_DIR):$(INC_DIR)


# ---------- Subjects ---------- #
MY_SOURCES = \
		main.c \
		check_arg.c

HEADERS = minishell.h

# ---------- Objects ---------- #
OBJ 	= $(addprefix $(OBJ_DIR)/, $(MY_SOURCES:.c=.o))



$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


debug: -Wall -Wextra -Werror -g -I inc/ -fsanitize=address


clean:
	@rm -rf $(OBJ_DIR)


fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)


re: fclean
	$(MAKE) all

.PHONY: re clean fclean all