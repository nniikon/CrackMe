ExecName = crack

all:
	gcc `pkg-config --cflags gtk+-3.0` main.c `pkg-config --libs gtk+-3.0` -L./-llibvlc -lvlc -o $(ExecName)

run: all
	./$(ExecName)
