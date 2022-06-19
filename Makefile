NAME = minishell
SRCS = src/main.c src/executor.c src/custom_readline.c\
       src/signal_handling.c src/env.c src/get_arguments.c\
	   src/get_path.c src/handle_bin.c src/set_input_utils.c\
	   src/handle_built_in.c src/handle_cmd.c src/init_minishell.c\
	   src/string_utils.c src/lexer/lekser_utils.c src/lexer/lekser.c\
	   src/lexer/open_evar.c src/lexer/relib.c src/lexer/lst_utils.c\
	   src/lexer/remove_spaces.c src/lexer/tokenizer.c src/lexer/parser_utils.c\
	   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
	   src/builtin/echo.c src/string_utils_2.c src/builtin/cd.c\
	   src/builtin/pwd.c src/builtin/env.c src/builtin/export.c\
	   src/builtin/unset.c src/builtin/exit.c src/handle_pipes.c\
	   src/set_input.c

OBJS = $(SRCS:%.c=%.o)
HEADER = minishell.h
READLINE_LIB = -Lreadline
READLINE_HEADER = -Ireadline
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
.PHONY = all clean fclean re

all: $(LIBFT) $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) readline/libreadline.a readline/libhistory.a -ltermcap $(OBJS) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@

$(LIBFT):
	make -s -C libft/

clean:
	make -s -C libft/ clean
	rm -f $(OBJS)

fclean: clean
	make -s -C libft/ fclean
	rm -f $(NAME)

re: fclean all
