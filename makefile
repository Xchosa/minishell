
NAME := minishell
CC := cc




LIBFT_PATH := libft_shell
LIBFT := $(LIBFT_PATH)/libft.a

GARBAGE_PATH := garbage_collector

INC_DIRS := Includes $(LIBFT_PATH) $(GARBAGE_PATH) src/executor src/parser src/parser/
SRC_DIRS := src