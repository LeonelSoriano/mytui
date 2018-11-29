/** @file mytui_config.h
*  @ingroup Conf
*  @brief costantes de colores y foreground de la terminal
*  @date 28-11-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __MYTUI_CONFIG__
#define __MYTUI_CONFIG__

#include <glib.h>
#include "until.h"

static const char* CONF_FONDER = ".config";
static const char* TUI_FOLDER_CONF = "mytui";
static const char* CONF_FILE_NAME = "init.conf";

/**
 * tiene la informacion del archivo de conf en memoria
 */
GHashTable* hash_conf;

#ifdef __MINGW32__
    static const char* SEPARATOR_FOLDER = "\\";
#else
    static const char* SEPARATOR_FOLDER = "/";
#endif

/**
* gestiona el inicio la conf de la libreria
*/
void ini_conf_file();

static void create_default_conf();

/**
 *  @brief verifica archivo de conf
 *  @return si el archivo de configuracion no existia y es creado es false
 *  verifica si existe los path y archivos de confi de la lab
 */
static bool verification_init_file();

static void get_file_conf_path(char* data);

#endif
