#ifndef __UNTIL__
#define __UNTIL__

#include <stdbool.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <glib.h>

#include "mytui_color.h"
#include "mytui_cmd.h"

//#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))
//#define SUM(...)  (sum(NUMARGS(__VA_ARGS__), __VA_ARGS__))

struct InfoTerm{
    unsigned int width;
    unsigned int height;
};

struct InfoTerm get_info_term();

/**
 * ... text ...
 */
void run_cmd_silent(const char *cmd);

void print_error( const char *msg, ...);

void print_info( const char *msg, ...);

bool exist_file(const char* path);

const char* get_home_folder();

GHashTable* read_file_conf();

#endif
