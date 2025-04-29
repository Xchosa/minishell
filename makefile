
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
LEXER_DIR = ./src/lexer
DEBUG_DIR = debug_dir
INC_DIR = inc
OBJ_DIR = obj

VPATH = $(SOURCE_DIR):$(PARSE_DIR)::$(LEXER_DIR)$(EXECUTER_DIR_DIR):$(INC_DIR)


# ---------- Subjects ---------- #
MY_SOURCES = \
		main.c \
		tty.c \
		scan_char_helper.c \
		tokeniser.c \
		heredoc.c \
		handle_quotes.c \
		update_line.c \
		tokeniser_print.c \
		lexer.c \
		lexer_helper.c \
		count_strings_up.c \
		bash_config.c 


HEADERS = \
		minishell.h \
		parser.h

# ---------- Objects ---------- #
OBJ 	= $(addprefix $(OBJ_DIR)/, $(MY_SOURCES:.c=.o))



$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C ./libft


debug: -Wall -Wextra -Werror -g -I inc/ -fsanitize=



clean:
	@rm -rf $(OBJ_DIR)
	make -C libft fclean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	make -C libft fclean


re: fclean
	$(MAKE) all

.PHONY: re clean fclean all