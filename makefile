#https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
#minoca
#termbox
#"hisotirial de git
#Plug 'cohama/agit.vim'
#Plug 'ap/vim-css-color'
#grep -H -r "<<<<<<< HEAD" ./
#Plug 'sodapopcan/vim-twiggy'
#gcc -L/home/lsoriano/dev/c/hol/mytui/termbox/hola/usr/lib/ -Wl,-rpath=/home/lsoriano/dev/c/hol/mytui/termbox/hola/usr/lib/ -Wall -o test main.c -ltermbox
#https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
#git submodule update --init --recursive
#https://shapeshed.com/vim-netrw/
#https://gist.github.com/danidiaz/37a69305e2ed3319bfff9631175c5d0f
#http://simplestcodings.blogspot.com/2010/09/simple-xml-parser-in-c-using-libxml.html
POST_L = -ltermbox #`pkg-config --cflags --libs glib-2.0`
CC=gcc
CFLAGS=-c -Wall  -pedantic-errors  -Wextra -std=c99   $(shell pkg-config --cflags glib-2.0)
LDFLAGS=   -L/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/leonel/dev/c/mytui/termbox/build/usr/lib/
SOURCES=main.c  ./src/until.c  ./src/mytui_config.c ./src/mytui.c ./src/mytui_buffer.c ./src/mytui_widget.c ./src/mytui_std_conf.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test

all: $(SOURCES)  $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)   $(LDFLAGS)  $(OBJECTS) $(POST_L)  -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f  $(OBJECTS) $(EXECUTABLE)

clean_doc:
	rm -rf ./html/
	rm -rf ./latex/

lnk:
	@ln -fs ./termbox/build/usr/include/termbox.h termbox.h

run:
	./$(EXECUTABLE)

#gcc -L/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wall -o test main.c -ltermbox
