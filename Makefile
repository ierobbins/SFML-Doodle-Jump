CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -std=gnu++11

run: main.o
	g++ main.o -o doodle $(CFLAGS)

main.o: main.cpp
	g++ -c main.cpp -I /usr/include/SFML

target: dependencies
	action

clean:
	rm *.o doodle
