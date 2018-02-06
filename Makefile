NAME	= libmy_malloc.so

CC	= gcc

RM	= rm -f

SRCS	= ./free.c \
	  ./malloc.c \
	  ./realloc.c \
	  ./pthread.c \
	  ./show_alloc_mem.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./
CFLAGS += -W -Wall -Wextra -g -fPIC

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -shared -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
