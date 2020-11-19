FLAGS = -g -Wall -Werror -std=c++14
RUNNAME = program4
.PHONY: program4 clean run

program4: Dynamic.o
	g++ $(FLAGS) Dynamic.o -o program4

Dynamic.o: Dynamic.cpp
	g++ -c $(FLAGS) Dynamic.cpp -o Dynamic.o

run: program4
	./$(RUNNAME)

clean:
	rm *.o $(RUNNAME)

memcheck: program4
	valgrind --leak-check=yes ./$(RUNNAME)
