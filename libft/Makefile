CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = libft.a

LIB_SRCS = $(shell ls *.c)
LIB_OBJS =  $(LIB_SRCS:.c=.o)

all: $(NAME)

$(NAME): ${LIB_SRCS}
	@${CC} ${CFLAGS} -c ${LIB_SRCS}
	ar -rcs $(NAME) $(LIB_OBJS)
	
clean:
	$(RM) $(LIB_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re