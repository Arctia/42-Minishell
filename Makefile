
NAME=minishell

CC=gcc

FLAGS= -g #-Wall -Werror -Wextra

INCS = ./global.h ./executor/executor.h ./parser/parser.h ./lexer/lexer.h \
		./glob.h

SRCS =	./main/signals2_0.c \
		./main/main.c \
		./main/free_structs.c \
		./main/init.c \
		./main/prompt.c \
		./lexer/lexer.c \
		./lexer/lexer_splitter.c \
		./lexer/lexer_syntax.c \
		./parser/parser.c \
		./parser/ps_utils.c \
		./parser/ps_write.c \
		./parser/ps_utils_2.c \
		./parser/ps_flags_red.c \
		./executor/executor.c \
		./executor/ft_execv.c \
		./executor/pipe.c \
		./executor/redirpipe.c \
		./executor/redir.c \
		./executor/executor_process.c \
		./expander/expander.c \
		./expander/expander_utils.c \
		./builtin/redirector.c \
		./builtin/unset.c \
		./builtin/cd.c \
		./builtin/echo.c \
		./builtin/env.c \
		./builtin/pwd.c \
		./builtin/exit.c \
		./expander/export.c \
		./expander/export2.c \
		./expander/export3.c \
		./expander/export_utils.c \
		./expander/export_utils2.c

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib


OBJS=$(SRCS:.c=.o)

%.o:%.c $(INCS)
		$(CC) $(FLAGS) -I$(READLINE)  -c $< -o $@
%.o:%.c $(INCS)
		$(CC) $(FLAGS) -I$(READLINE_DIR)/include  -c $< -o $@

LIBFT=./libft/libft.a

 #READLINE = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib \
 				-I$(HOME)/.brew/opt/readline/include

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(FLAGS) $(SRCS) $(LIBFT) $(READLINE_LIB) -o $(NAME)
#$(READLINE)

$(LIBFT):
		$(MAKE) -C ./libft/

all:$(NAME)

clean:
		rm -f *.o
		rm -f main/*.o
		rm -f minishell_lexer/lexer/*.o
		rm -f parser/*.o
		rm -f executor/*.o
		$(MAKE) clean -C ./libft

fclean: clean
		rm -f $(NAME)
		$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
