
NAME := minishell
CC := cc

#---------linux---------
CFLAGS	= -Wall -Wextra -Werror -g -I inc/ -ldl -lglfw -pthread -lm
#----------mac ---------
CFLAGS		= -Wall -Wextra -Werror -g -I inc/


LIBFT_PATH := libft_shell
LIBFT := $(LIBFT_PATH)/libft.a

GARBAGE_PATH := garbage_collector

INC_DIRS := Includes $(LIBFT_PATH) $(GARBAGE_PATH) src/executor src/parser src/parser/
SOURCE_DIR = ./src
PARSE_DIR = ./src/parser
EXECUTER_DIR = ./src/executer
INC_DIR = inc
OBJ_DIR = obj

VPATH = $(SOURCE_DIR):$(PARSE_DIR):$(EXECUTER_DIR_DIR):$(INC_DIR)


# ---------- Subjects ---------- #
MY_SOURCES = \
		main.c \
		check_arg.c


# ---------- Objects ---------- #
OBJ 	= $(addprefix $(OBJ_DIR)/, $(MY_SOURCES:.c=.o))