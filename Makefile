PARSER = parser

INC_DIR = include

PARSER_INC = $(INCLUDE)/parser

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

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

HADERS = $(UTILS_HEADERS) \
			$(PARSER_HEADERS) \

$(OBJS_DIR)/%.o: %.c
	$(CC) -I $(PARSER_INC) -I $(INC_DIR) -c $< -o $@

$(PARSER): $(HADERS) $(OBJS) 
	$(CC) -I $(PARSER_INC) -I $(INC_DIR) $(OBJS) -o $@


all: $(PARSER)

test:
	@echo $(OBJS)

