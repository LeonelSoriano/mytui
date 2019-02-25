#clogedaria
#https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
#minoca
#termbox
#"hisotirial de git
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
#amixer -D pulse sset Master 50%+
#https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/developer_guide/debugging-running-application
#https://sourcegraph.com/github.com/neovim/neovim/-/blob/src/nvim/tui/terminfo.c

#compilar remoto
#gdbserver :12345 ./yourapplication
#gdb -x debug.gdb
#target remote localhost:12345

#save breakpoints <filename>
# source <filename>
#set history save on
#set history filename ~/.gdb_history
#set history size <size>
#frame actual linea
#list codigo
#break en file  break /Full/path/to/service.cpp:45
#inflo variables, info locals, info args


#https://www.sanfoundry.com/c-program-queue-using-linked-list/
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

POST_L = -ltermbox #`pkg-config --cflags --libs glib-2.0`
CC=gcc
CFLAGS=-c -g -Wall  -pedantic-errors  -Wextra -std=c99 -D _POSIX_C_SOURCE=200809L    $(shell pkg-config --cflags glib-2.0)
LDFLAGS= -L$(ROOT_DIR)/termbox/build/usr/lib/ -Wl,-rpath=$(ROOT_DIR)/termbox/build/usr/lib/

MAIN=main.c
MAIN_TEST=./test/test.c

SOURCES=./src/until.c  ./src/mytui_config.c ./src/mytui.c ./src/mytui_buffer.c ./src/mytui_widget.c ./src/mytui_std_conf.c ./src/mytui_container_tui.c ./src/mytui_mouse_manager.c ./src/mytui_animation.c ./src/mytui_debug_system.c ./src/mytui_logger.c


OBJECTS =  $(SOURCES:.c=.o)
OBJECTS_MAIN = $(MAIN:.c=.o) $(SOURCES:.c=.o)
OBJECTS_TEST = $(MAIN_TEST:.c=.o) $(SOURCES_TEST:.c=.o)

SOURCES_TEST=#./test/test.c

LDLIBS_TEST = -lcmocka -fprofile-arcs -ftest-coverage
LDFLAGS_TEST = -Wl,--wrap=write -Wl,--wrap=read



EXECUTABLE=mytui

EXECUTABLE_TEST=mytui_test

all: $(MAIN) $(SOURCES)  $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_MAIN)
	$(CC)   $(LDFLAGS)  $(OBJECTS_MAIN) $(POST_L)  -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f  $(OBJECTS) $(EXECUTABLE)
	rm -f $(OBJECTS_TEST) $(EXECUTABLE_TEST)

clean_doc:
	rm -rf ./html/
	rm -rf ./latex/


unit: $(MAIN_TEST) $(SOURCES_TEST) $(SOURCES)  $(EXECUTABLE_TEST)

$(EXECUTABLE_TEST): $(OBJECTS_TEST) $(OBJECTS)
	$(CC)   $(LDFLAGS) $(LDFLAGS_TEST) $(OBJECTS) $(OBJECTS_TEST) $(POST_L) $(LDLIBS_TEST)   -o $@

doc:
	doxygen

lnk:
	@ln -fs ./termbox/build/usr/include/termbox.h termbox.h


run:
	./$(EXECUTABLE)

#gcc -L/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wl,-rpath=/home/leonel/dev/c/mytui/termbox/build/usr/lib/ -Wall -o test main.c -ltermbox

