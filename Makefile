NAME  = nanoshell

SOURCE = nanoshell.c

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

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS) -o $(NAME)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

test:
	$(OBJ)


# gcc main.c -lreadline
