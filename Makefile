
NAME := minishell
CC := cc

#---------linux---------
CFLAGS	= -Wall -Wextra  -g -I inc/ -ldl -lglfw -pthread -lm #-Werror
#----------mac ---------
CFLAGS		= -Wall -Wextra -g -I inc/ #-Werror

LIBFT := ./libft/libft.a

SOURCE_DIR = ./src
PARSE_DIR = ./src/parser
TOKEN_DIR = ./src/parser/string_to_token
EXPORT_DIR = ./src/parser/export_case
CMD_LIST_DIR = ./src/parser/cmd_list
EXECUTER_DIR = ./src/executer
LEXER_DIR = ./src/lexer
SIGNAL_DIR = ./src/signal
HEREDOC_DIR = ./src/executer/heredoc
DEBUG_DIR = debug_dir
INC_DIR = inc
OBJ_DIR = obj

VPATH = $(SOURCE_DIR):$(PARSE_DIR):$(SIGNAL_DIR):$(TOKEN_DIR):\
$(LEXER_DIR):$(CMD_LIST_DIR):$(EXPORT_DIR):$(EXECUTER_DIR):$(HEREDOC_DIR):$(INC_DIR)


# ---------- Subjects ---------- #
MY_SOURCES = \
		test_main.c \
		handler.c \
		main.c \
		tty.c \
		clean_up.c \
		skip_whitespace_helper.c \
		scan_char_helper.c \
		abort_parser.c \
		get_token_fk.c \
		tokeniser.c \
		heredoc.c \
		handle_quotes.c \
		update_line.c \
		update_line_helper.c \
		tokeniser_print.c \
		lexer.c \
		lexer_identifer.c \
		lexer_helper.c \
		lexer_tokens.c \
		count_strings_up.c \
		bash_config.c \
		exit_codes_config.c \
		tokens_to_export.c \
		append_export_str.c \
		create_export_tokens.c \
		handle_export.c \
		extend_token_from_bash.c \
		extract_token_from_bash.c \
		extract_token_from_bash_2.c \
		parse_token_to_bash.c \
		handle_dollar.c \
		print_cmd_lst.c \
		define_cmd_typ.c \
		init_cmd_nodes.c \
		token_redir_to_cmd.c \
		tokens_list_to_cmd.c \
		tokens_text_to_cmd.c \
		debug.c \
		builtins.c \
		manage_pipes.c \
		pipex.c \
		special_builtin.c \
		executer.c \
		redirect.c \
		handler.c \
		signal_main.c \
		find_heredoc.c



HEADERS = \
		minishell.h \
		parser.h \
		executer.h \
		signal_tp.h \
		debug.h

# ---------- Objects ---------- #
OBJ 	= $(addprefix $(OBJ_DIR)/, $(MY_SOURCES:.c=.o))

all: $(NAME)
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C ./libft


debug: -Wall -Wextra -Werror -g -I inc/ -fsanitize=


.PHONY: re clean fclean all libft_fclean

libft_fclean:
	@if [ -d "./libft" ]; then make -C libft fclean; fi 

fclean: clean libft_fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean
	$(MAKE) all
