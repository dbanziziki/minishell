PARSER = parser

LIST = list

RM = rm -f

INC_DIR = include

PARSER_INC = $(INC_DIR)/parser

LIST_INC = $(INC_DIR)/list

SRCS_DIR = srcs

CC = gcc

CFLAGS = -g -fsanitize=address

PARSER_DIR = $(SRCS_DIR)/parser

MAIN = $(SRCS_DIR)/main.c

OBJS_DIR = objs

UTILS_DIR = $(SRCS_DIR)/utils

LIST_DIR = $(SRCS_DIR)/list

UTILS_HEADERS = $(addprefix $(INC_DIR)/, \
								utils.h \
)

PARSER_HEADERS = $(addprefix $(PARSER_INC)/, \
								parser.h \
								tokenizer.h \
								AST.h \
)

PARSER_SRCS = $(addprefix $(PARSER_DIR)/, \
								parser.c \
								tokenizer.c \
								AST.c \
								main.c \
)

LIST_HEADERS = $(addprefix $(LIST_INC)/, \
							list.h \
)

UTILS_SRCS = $(addprefix $(UTILS_DIR)/, \
							utils.c \
)

LIST_SRCS = $(addprefix $(LIST_DIR)/, \
							list.c \
)

SRCS = $(PARSER_SRCS) \
		$(UTILS_SRCS) \

HADERS = $(UTILS_HEADERS) \
			$(PARSER_HEADERS) \

#OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJS = $(SRCS:.c=.o)
LIST_OBJS = $(LIST_SRCS:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -I $(PARSER_INC) -I $(INC_DIR) -I $(LIST_INC) -c $< -o $@

$(PARSER): $(OBJS) $(LIST_OBJS) $(HADERS)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(PARSER_INC) -I $(LIST_INC) $(OBJS) -o $@

$(LIST): $(LIST_OBJS)
	$(CC) $(CFLAGS) -I $(LIST_INC) $(LIST_OBJS) $(LIST_DIR)/main.c -o $@

all: $(PARSER)

run: re all
	./$(PARSER)

re: fclean all

clean:
	$(RM) $(OBJS) $(LIST_OBJS)

fclean: clean
	$(RM) $(PARSER) $(LIST)

test:
	@echo $(INC_DIR)

