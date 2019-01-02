#clogedaria
#https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
#minoca
#termbox
#"hisotirial de git
#Plug 'cohama/agit.vim'
#Plug 'ap/vim-css-color'
#grep -H -r "<<<<<<< HEAD" ./
#https://jonasjacek.github.io/colors/
#https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
#git submodule update --init --recursive
#https://shapeshed.com/vim-netrw/
#https://gist.github.com/danidiaz/37a69305e2ed3319bfff9631175c5d0f
#http://simplestcodings.blogspot.com/2010/09/simple-xml-parser-in-c-using-libxml.html
#sudo pacman -Syy
#sudo pacman -Su

#https://www-zeuthen.desy.de/unix/unixguide/infohtml/gdb/Server.html
#https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/developer_guide/debugging-running-application
#https://stackoverflow.com/questions/2308653/can-i-use-gdb-to-debug-a-running-process/2308664
#https://sourcegraph.com/github.com/neovim/neovim/-/blob/src/nvim/tui/terminfo.c
POST_L = -ltermbox #`pkg-config --cflags --libs glib-2.0`
CC=gcc
CFLAGS=-c -g -Wall  -pedantic-errors  -Wextra -std=c99   $(shell pkg-config --cflags glib-2.0)
LDFLAGS=   -L/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/leonel/dev/c/mytui/termbox/build/usr/lib/
SOURCES=main.c  ./src/until.c  ./src/mytui_config.c ./src/mytui.c ./src/mytui_buffer.c ./src/mytui_widget.c ./src/mytui_std_conf.c ./src/mytui_container_tui.c
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

doc:
	doxygen

lnk:
	@ln -fs ./termbox/build/usr/include/termbox.h termbox.h

run:
	./$(EXECUTABLE)

#gcc -L/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wall -o test main.c -ltermbox
