NAME = masterboy
FILES = generating_random_code.c main.c valid_user_input.c checking_piece_placements.c parameters.c
OBJ = generating_random_code.o main.o valid_user_input.o checking_piece_placements.o parameters.o
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ): $(FILES)
	gcc -c $(FILES)

clean:
	rm generating_code.o , header.o , main.o , verification_code.o

fclean: clean
	rm  masterboy.exe