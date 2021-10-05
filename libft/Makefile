NAME = libft.a

AR = ar rcs

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =	ft_bzero.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_realloc.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_atoi.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strmapi.c \
		ft_split.c \
		ft_itoa.c \
		ft_strtrim.c \
		ft_strnew.c \
		get_next_line.c \
		ft_strndup.c \
		ft_strcmp.c \
		ft_free_strtab.c \
		ft_isspace.c \
		ft_strjoin_free_both.c \

BONUS =	ft_lstnew.c \
		ft_lstmap.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \

OBJS = $(SRCS:.c=.o)

BONUSOBJS = $(BONUS:.c=.o)

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJS) $(BONUSOBJS)
	@$(AR) $@ $^

bonus: $(OBJS) $(BONUSOBJS)
	@$(AR) $(NAME) $(OBJS) $(BONUSOBJS)

all:	$(NAME)

clean:
	@$(RM) $(OBJS) $(BONUSOBJS)

fclean:	clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY: 	all fclean clean re
