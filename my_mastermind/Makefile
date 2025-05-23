NAME = masterboy
FILES = generating_code.c main.c verification_code.c
OBJ = generating_code.o main.o verification_code.o
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