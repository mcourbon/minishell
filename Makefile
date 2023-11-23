LIBFT = libft.a

NAME = minishell
SRC_FILES = sources/cd.c \
			sources/check_quotes.c \
			sources/echo_utils.c \
			sources/echo_utils2.c \
			sources/echo.c \
			sources/env.c \
			sources/envp_utils.c \
			sources/envp_utils2.c \
			sources/export_exec.c \
			sources/export.c \
			sources/export_utils.c \
			sources/find_path.c \
			sources/free.c \
			sources/init.c \
			sources/is_builtin.c \
			sources/is_echo.c \
			sources/list.c \
			sources/main.c \
			sources/parsing_command.c \
			sources/pipe.c \
			sources/pwd.c \
			sources/redir_exec.c \
			sources/redir_in_management.c \
			sources/redir_out_management.c \
			sources/redir.c \
			sources/run_simple.c \
			sources/signals.c \
			sources/unset.c \
			sources/utils.c \

OBJ_FILES = ${SRC_FILES:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I /goinfre/homebrew/opt/readline/include
READLINE = -lreadline -L /goinfre/homebrew/opt/readline/lib
HEADER = headers/minishell.h
RM = rm -rf

all: libft $(NAME)

libft:
	make -C libs/Libft

%.o: %.c $(HEADER) Makefile libs/Libft/$(LIBFT)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ_FILES) libs/Libft/$(LIBFT)
		$(CC) $(OBJ_FILES) -I $(HEADER) libs/Libft/$(LIBFT) $(READLINE) -o $(NAME)

clean :
		make clean -C libs/Libft
		${RM} ${OBJ_FILES}

fclean : clean
		make fclean -C libs/Libft
		${RM} $(NAME)
		${RM} $(LIBFT)


re : fclean all


.PHONY : all clean fclean re libft