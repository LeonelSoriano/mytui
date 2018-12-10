#https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
#minoca
#termbox
#gcc -L/home/lsoriano/dev/c/hol/mytui/termbox/hola/usr/lib/ -Wl,-rpath=/home/lsoriano/dev/c/hol/mytui/termbox/hola/usr/lib/ -Wall -o test main.c -ltermbox
#https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
#git submodule update --init --recursive
POST_L = -ltermbox #`pkg-config --cflags --libs glib-2.0`
CC=gcc 
CFLAGS=-c -Wall  -pedantic-errors  -Wextra -std=c99   $(shell pkg-config --cflags glib-2.0)
LDFLAGS=   -L/home/lsoriano/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/lsoriano/dev/c/mytui/termbox/build/usr/lib/
SOURCES=main.c  ./src/until.c  ./src/mytui_config.c ./src/mytui.c ./src/mytui_buffer.c ./src/mytui_widget.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test

all: $(SOURCES)  $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC)   $(LDFLAGS)  $(OBJECTS) $(POST_L)  -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f  $(OBJECTS) $(EXECUTABLE)

lnk:
	@ln -fs ./termbox/build/usr/include/termbox.h termbox.h

#gcc -L/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wall -o test main.c -ltermbox
