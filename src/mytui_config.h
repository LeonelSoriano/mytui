/** @file mytui_config.h
 *  @ingroup Conf
 *  @brief costantes de colores y foreground de la terminal
 *  @date 28-11-2018
 *  @author leonelsoriano3@gmail.com
 */
#ifndef __MYTUI_CONFIG__
#define __MYTUI_CONFIG__

//#include <glib.h>
#include <stdbool.h>
#include <string.h>

#include "mytui_std_conf.h"
#include "until.h"

typedef struct ConfMap {
    char *key;
    char *value;
    struct ConfMap *next;
} ConfMap;

/**
 * tiene la informacion del archivo de conf en memoria
 */
// GHashTable* hash_conf;

#ifdef __MINGW32__
static const char *SEPARATOR_FOLDER = "\\";
#else
static const char *SEPARATOR_FOLDER = "/";
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
void conf_map_add(ConfMap **confMap, char *key, char *value);

void free_conf_map(ConfMap **confMap);

void load_conf_map(ConfMap **confMap);

const char *getValueConf(ConfMap *confMap, const char *key);

/**
 * resolve el valor de configuración si se envía al componente es este, de lo
 * contrario busca en memoria la configuración cargada a memoria si no busca la
 * OJO no sirve en hilos de ejecución usa static para el return
 * por defecto
 * @param hash de la configuración
 * @param typo o código de la configuración
 * @param valor enviado del componente si es "" o " " or null no se toma en
 *  cuenta
 * @return color luego de ser resuelto
 */
char *resolve_value(ConfMap *ConfMap, char *type_conf, const char *component_value);

/**
 *  busca unvalor en la conf standar
 * @param configuracion a buscar
 * @return valor correspondiente al key
 */
char *find_std_values(char *type_conf);

/**
 * resuelve el color y lo convierte a int
 * @param diccionario de key value de configuracion
 * @param coloque se tiene en el widget
 * @param str estandar en la conf
 * @return color luego de ser resuelto por la logica
 */
int resolve_color(ConfMap *_confMap, int actual_color, char *str_conf);

#endif
