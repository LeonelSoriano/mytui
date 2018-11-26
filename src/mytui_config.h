#ifndef __MYTUI_CONFIG__
#define __MYTUI_CONFIG__

#include <glib.h>


#include "until.h"

static const char* CONF_FONDER = ".config";
static const char* TUI_FOLDER_CONF = "mytui";
static const char* CONF_FILE_NAME = "init.conf";

GHashTable* hash_conf;

#ifdef __MINGW32__
    static const char* SEPARATOR_FOLDER = "\\";
#else
    static const char* SEPARATOR_FOLDER = "/";
#endif

void ini_conf_file();


static void verification_init_file();

#endif
