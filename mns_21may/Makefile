CC		= gcc
NAME	= minishell
CFLAGS	= -Wall -Werror -Wextra

SRC_DIR = ./src/
LIB_DIR = ./lib/
INC_DIR = ./include/

SRC_FILES = $(shell ls $(SRC_DIR) | grep .c)
OBJ_FILES = $(SRC_FILES:.c=.o)
INC_FILES = $(shell ls $(INC_DIR) | grep .h)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(LIB_DIR), $(OBJ_FILES))
INC = $(addprefix  $(INC_DIR), $(INC_FILES))

LIBFT = ./libft/libft.a
FTDIR = libft
FTSRC = $(shell ls ./libft/*.c)

all: $(READLINE) $(NAME)

$(READLINE):
	echo 	"readline indiriliyor" 
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(NAME): $(LIBFT) $(LIB_DIR) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $@ 

$(LIBFT): $(FTSRC)
	make -C libft

$(LIB_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) -c $(CFLAGS) -I $(INC_DIR)  $< -o $@

$(LIB_DIR):
	mkdir lib

run:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell

clean:
	make clean -C libft/
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re