#https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
#minoca
#termbox
#gcc -L/home/lsoriano/dev/c/hol/mytui/termbox/hola/usr/lib/ -Wl,-rpath=/home/lsoriano/dev/c/hol/mytui/termbox/hola/usr/lib/ -Wall -o test main.c -ltermbox
#https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
GTK = `pkg-config --cflags --libs glib-2.0`
CC=gcc
CFLAGS=-c -Wall  -pedantic-errors  -Wextra -std=c99 $(shell pkg-config --cflags glib-2.0) -I./termbox/hola/usr/include/
LDFLAGS= -L./termbox/hola/usr/lib/libtermbox.so.1.0.0
SOURCES=main.c ./src/until.c  ./src/mytui_config.c ./src/mytui.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test

all: $(SOURCES)  $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS)  $(OBJECTS) $(GTK) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f  $(OBJECTS) $(EXECUTABLE)

