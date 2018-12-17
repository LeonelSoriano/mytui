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
    char *key;
    char *value;
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
void conf_map_add(ConfMap **confMap,  char* key,  char* value);

void free_conf_map(ConfMap **confMap);

void load_conf_map(ConfMap **confMap);

const char* getValueConf(ConfMap *confMap, const char* key);

/**
 * resolve el valor de configuracion si se envia al componente es este, de lo
 * contrario busca en memoria la configuracion cargada a memoria si no busca la
 * por defecto
 * @param hash de la configuracion
 * @param typo o codigo de la configuracion
 * @param valor enviado del componente si es "" o " " or null no se toma en 
 *  cuenta
 * @return color luego de ser resuelto
 */
char* resolve_value( ConfMap *ConfMap,char *type_conf,char* component_value);
#endif
