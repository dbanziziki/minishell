PARSER = parser

NAME = minishell

LIST = list

TEST_DIR = tests

RM = rm -f

INC_DIR = include

PARSER_INC = $(INC_DIR)/parser

READLINE_FLAG =  

LIST_INC = $(INC_DIR)/list

SRCS_DIR = srcs

CC = gcc

CFLAGS = -g -fsanitize=address

PARSER_DIR = $(SRCS_DIR)/parser

MAIN = $(SRCS_DIR)/main.c

OBJS_DIR = objs

UTILS_DIR = $(SRCS_DIR)/utils

LIST_DIR = $(SRCS_DIR)/list

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
								tokenizer_helper.c \
								parse_word.c \
)

PARSER_MAIN = $(PARSER_DIR)/main.c

MINISHELL_MAIN = $(SRCS_DIR)/minishell.c

LIST_HEADERS = $(addprefix $(LIST_INC)/, \
							list.h \
)

UTILS_SRCS = $(addprefix $(UTILS_DIR)/, \
							utils.c \
)

LIST_SRCS = $(addprefix $(LIST_DIR)/, \
							list.c \
)

MINISHELL_SRCS = $(addprefix $(SRCS_DIR)/, \
								minishell.c \
)

SRCS_PARSER = $(PARSER_SRCS) \
			$(UTILS_SRCS) \
			$(LIST_SRCS) \
			#$(PARSER_MAIN) \

SRCS_MINISHELL = $(PARSER_SRCS) \
			$(UTILS_SRCS) \
			$(LIST_SRCS) \
			$(MINISHELL_SRCS) \

HEADERS = $(UTILS_HEADERS) \
			$(PARSER_HEADERS) \

#OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJS = $(SRCS_PARSER:.c=.o)
MINISHELL_OBJS = $(SRCS_MINISHELL:.c=.o)
LIST_OBJS = $(LIST_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS_DIR:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(PARSER_INC) -I $(INC_DIR) -I $(LIST_INC) -c $< -o $@

$(NAME): $(MINISHELL_OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(READLINE_FLAG) -I $(INC_DIR) -I $(PARSER_INC) -I $(LIST_INC) $(MINISHELL_OBJS) -o $@

$(PARSER): $(OBJS) $(LIST_OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(PARSER_INC) -I $(LIST_INC) $(OBJS) -o $@

test: $(OBJS) $(TEST_OBJS)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(PARSER_INC) -I $(LIST_INC) $(OBJS) $(TEST_OBJS) -o $@

$(LIST): $(LIST_OBJS)
	@$(CC) $(CFLAGS) -I $(LIST_INC) $(LIST_OBJS) $(LIST_DIR)/main.c -o $@

all: $(NAME)

run: re all
	./$(NAME)

re: fclean all

clean:
	@$(RM) $(OBJS) $(LIST_OBJS) $(MINISHELL_OBJS)

fclean: clean
	@$(RM) $(PARSER) $(LIST) $(NAME)


