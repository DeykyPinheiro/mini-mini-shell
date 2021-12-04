NAME  = nanoshell

SOURCE = cmd_handler.c exec_argc_piped.c exec_args.c init_shell.c nanoshell.c
SOURCE += parse_space.c print_dir.c process_string.c take_input.c

SOURCE_DIR = ./src
OBJECT_DIR = ./obj

AR = ar
ARFLAGS = rcs

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

LINKS = -lreadline


OBJ = $(addprefix $(OBJECT_DIR)/,$(SOURCE:%.c=%.o))


all: $(NAME)


$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

$(NAME): $(OBJECT_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS) -o $(NAME)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj

fclean:	clean
	$(RM) $(NAME)

re: fclean all

run:
	./nanoshell


# gcc main.c -lreadlin-lreadlinee
# ctrl + shit + v -> abre o previw do readme.md
