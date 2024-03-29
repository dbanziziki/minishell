PARSER = parser

LIBFT_LIB = libft.a

NAME = minishell

LIST = list

LIBFT_INC_DIR = libft

LIBFT_DIR = libft

TEST_DIR = tests

RM = rm -f

OBJS_DIR = objs

OSNAME = $(shell uname -s)

INC_DIR = include

PARSER_INC = $(INC_DIR)/parser

READLINE_FLAG = -L/usr/include  -lreadline

LIST_INC = $(INC_DIR)/list

SRCS_DIR = srcs

CC = gcc

RPATH = /Users/$(USER)/.brew/opt/readline/

ifeq ($(OSNAME), Linux)
	RFLAGS = 
	LINUX_FALG = -L /usr/include -lreadline
endif

ifeq ($(OSNAME), Darwin)
	RFLAGS = -L $(RPATH)lib -I $(RPATH)include -lreadline -Wno-unused-command-line-argument
endif
CFLAGS = -Wall -Wextra -Werror #-g #-fsanitize=address #

PARSER_DIR = $(SRCS_DIR)/parser

MAIN = $(SRCS_DIR)/main.c

OBJS_DIR = objs

MINISHELL_INC_DIR = $(INC_DIR)/$(NAME)

UTILS_DIR = $(SRCS_DIR)/utils

BUILDIN_DIR = $(SRCS_DIR)/buildin

LIST_DIR = $(SRCS_DIR)/list

BUILDIN_SRCS_DIR = $(addprefix $(BUILDIN_DIR)/, \
						echo.c \
						find_cmd.c \
						export.c \
						unset.c \
						cd.c \
)

TEST_SRCS_DIR = $(addprefix $(TEST_DIR)/, \
						parser_pipe_test.c \
)

UTILS_HEADERS = $(addprefix $(INC_DIR)/, \
								utils.h \
)

PARSER_HEADERS = $(addprefix $(PARSER_INC)/, \
								parser.h \
								tokenizer.h \
								AST.h \
								tokens.h \
)

PARSER_SRCS = $(addprefix $(PARSER_DIR)/, \
								parser.c \
								tokenizer.c \
								AST.c \
								tokenizer_utils.c \
								parse_word.c \
								AST_utils.c \
								parse_redirection.c \
								parse_quotes.c \
								parse_single_quotes.c \
								parser_utils.c \
								parse_env_var.c \
								parse_heredoc.c \
								parse_pipe.c \
								parse_env_var_utils.c \
								token.c \
								tokenize_quotes.c \
								tokenize_quotes_utils.c \
)

MINISHELL_MAIN = $(SRCS_DIR)/minishell.c

LIST_HEADERS = $(addprefix $(LIST_INC)/, \
							list.h \
)

MINISHELL_HEADERS = $(addprefix $(INC_DIR)/$(NAME)/, \
								minishell.h \
)

UTILS_SRCS = $(addprefix $(UTILS_DIR)/, \
							utils.c \
							free_all.c \
							exit_minishell.c \
							print_error.c \
)

LIST_SRCS = $(addprefix $(LIST_DIR)/, \
							list.c \
)

MINISHELL_SRCS = $(addprefix $(SRCS_DIR)/$(NAME)/, \
								minishell.c \
								cmd_and_args.c \
								minishell_utils.c \
								signals.c \
								heredoc.c \
								redirections.c \
								pipes.c \
								exec_cmd.c \
								init_minishell.c \
)

SRCS_PARSER = $(PARSER_SRCS) \
			$(UTILS_SRCS) \
			$(LIST_SRCS) \
			#$(PARSER_MAIN) \

SRCS_MINISHELL = $(PARSER_SRCS) \
			$(UTILS_SRCS) \
			$(LIST_SRCS) \
			$(MINISHELL_SRCS) \
			$(BUILDIN_SRCS_DIR) \

HEADERS = $(UTILS_HEADERS) \
			$(PARSER_HEADERS) \

#OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJS = $(SRCS_PARSER:.c=.o)
MINISHELL_OBJS = $(SRCS_MINISHELL:.c=.o)
LIST_OBJS = $(LIST_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS_DIR:.c=.o)
BUILTIN_OBJS = $(BUILDIN_SRCS_DIR:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) $(RFLAGS) -I $(PARSER_INC) -I $(INC_DIR) -I $(LIST_INC) -I $(MINISHELL_INC_DIR) -I $(LIBFT_INC_DIR) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(MINISHELL_OBJS) $(HEADERS) $(MINISHELL_HEADERS)
	@$(CC) $(CFLAGS) $(RFLAGS) -I $(INC_DIR) -I $(PARSER_INC) -I $(LIST_INC) -I $(MINISHELL_INC_DIR) -I $(LIBFT_INC_DIR) $(MINISHELL_OBJS) $(LIBFT_DIR)/$(LIBFT_LIB) $(LINUX_FALG) -o $@

#LIBFT
libft: $(LIBFT_LIB)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

LIBFT_NAME = libft

$(LIBFT_NAME)_clean:
	@make clean -C $(LIBFT_DIR)

$(LIBFT_NAME)_fclean:
	@make fclean -C $(LIBFT_DIR)

all: $(NAME)

run: re all
	./$(NAME)

re: fclean all $(LIBFT_NAME)_fclean

print:
	@echo $(MINISHELL_INC_DIR)

clean: $(LIBFT_NAME)_clean
	@$(RM) $(OBJS) $(LIST_OBJS) $(MINISHELL_OBJS)

fclean: clean $(LIBFT_NAME)_fclean
	@$(RM) $(PARSER) $(LIST) $(NAME)


