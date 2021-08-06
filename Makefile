PARSER = parser

RM = rm -f

INC_DIR = include

PARSER_INC = $(INC_DIR)/parser

SRCS_DIR = srcs

CC = gcc

PARSER_DIR = $(SRCS_DIR)/parser

MAIN = $(SRCS_DIR)/main.c

OBJS_DIR = objs

UTILS_DIR = $(SRCS_DIR)/utils

UTILS_HEADERS = $(addprefix $(INC_DIR)/, \
								utils.h \
)

PARSER_HEADERS = $(addprefix $(PARSER_INC)/, \
								parser.h \
								tokenizer.h \
)

PARSER_SRCS = $(addprefix $(PARSER_DIR)/, \
								parser.c \
								tokenizer.c \
)

UTILS_SRCS = $(addprefix $(UTILS_DIR)/, \
							utils.c \
)

SRCS = $(PARSER_SRCS) \
		$(UTILS_SRCS) \

HADERS = $(UTILS_HEADERS) \
			$(PARSER_HEADERS) \

#OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) -I $(PARSER_INC) -I $(INC_DIR) -c $< -o $@

$(PARSER): $(OBJS) $(HADERS)
	$(CC) -I $(PARSER_INC) -I $(INC_DIR) $(OBJS) -o $@

all: $(PARSER)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(PARSER)

test:
	@echo $(OBJS)

