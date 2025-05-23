all : $(TARGET)

$(helloworld) : $(helloworld.OBJ)
	gcc $(CFLAGS) -o $(helloworld) $(helloworld.OBJ)

$(helloworld.OBJ) : $(helloworld.cpp)
	gcc $(CFLAGS) -c $(helloworld.cpp)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all