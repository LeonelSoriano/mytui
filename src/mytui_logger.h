#ifndef __MYTUI_LOGGER_H__
#define __MYTUI_LOGGER_CONF_H__

#include "until.h"
#include <dirent.h>

/**
 * inicia el comopnente de logger
 */
void init_mytui_logger();

/**
 * libera los componentes de logger
 */
void free_mytui_logger();


/**
 * imprime una linea en los logger
 * @param formato que imprimer
 * @param parametros que se agregaran al formato
 */
void print_line_log(const char *msg, ...);

#endif
