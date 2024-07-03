CC		= gcc
NAME	= minishell
CFLAGS	= -g -Wall -Werror -Wextra -I $(READLINE_INC_LOC)

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

READLINE_LIB_LOC = readline/lib
READLINE_INC_LOC = readline/include
READLINE = $(READLINE_LIB_LOC)/libreadline.a
HISTORY = $(READLINE_LIB_LOC)/libhistory.a
READLINE_INIT_FILE_LOC = ~/

all:$(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	@echo $(PWD)
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install
	echo "set echo-control-characters 0" > $(READLINE_INIT_FILE_LOC).inputrc
	rm -rf readline-8.2 readline-8.2.tar.gz

$(NAME): $(LIBFT) $(LIB_DIR) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -L $(READLINE_LIB_LOC) -lreadline -lhistory -o $@ 

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
	@rm -rf readline readline-8.2 readline-8.2.tar.gz
	
test: all
	cd minishell_tester/ && ./tester

re: fclean all
re2: clean all

.PHONY: all clean fclean re re2 run test