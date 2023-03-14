
NAME=minishell

CC=gcc

FLAGS= -g -Wall -Werror -Wextra

INCS = ./global.h ./executor/executor.h ./parser/parser.h

SRCS =	./main/signals2_0.c \
		./main/signals.c \
		./main/main.c \
		./main/free_structs.c \
		./lexer/lexer.c \
		./lexer/lexer_splitter.c \
		./parser/parser.c \
		./parser/ps_utils.c \
		./executor/executor.c \
		./executor/ft_execv.c \
		./executor/pipe.c \
		./executor/redir.c \
		./expander/expander.c \
		./expander/expander_utils.c

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib



OBJS=$(SRCS:.c=.o)

%.o:%.c $(INCS)
		$(CC) $(FLAGS) -I$(READLINE_DIR)/include  -c $< -o $@

LIBFT=./libft/libft.a

# READLINE = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib \
# 				-I$(HOME)/.brew/opt/readline/include

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
