/** @file mytui_config.h
*  @ingroup Conf
*  @brief costantes de colores y foreground de la terminal
*  @date 28-11-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __MYTUI_CONFIG__
#define __MYTUI_CONFIG__

//#include <glib.h>
#include <string.h>
#include "until.h"
#include "mytui_std_conf.h"

typedef struct ConfMap{
    const char *key;
    const char *value;
    struct ConfMap  *next;
}ConfMap;

/**
 * tiene la informacion del archivo de conf en memoria
 */
//GHashTable* hash_conf;

#ifdef __MINGW32__
    static const char* SEPARATOR_FOLDER = "\\";
#else
    static const char* SEPARATOR_FOLDER = "/";
#endif

/**
* gestiona el inicio la conf de la libreria
*/
void ini_conf_file();


void init_conf_map(ConfMap *confMap);

/**
 * agrega un key/value al hash de configuracion en memoria
 * @param hash de la configuracion
 * @param el key a agregar
 * @param el value a agregar
 */
void add_conf_map_add(ConfMap **confMap, const char* key, const char* value);

#endif
