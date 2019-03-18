#ifndef __MYTUI_LOGGER_CONF_H__
#define __MYTUI_LOGGER_CONF_H__

#include "until.h"
#include <dirent.h>

/**
 * @brief enumeración de tipo de mensajes en el logger.
 *
 */
typedef enum {
    MytuiLoggerTypeError = 1, /**< tipo error */
    MytuiLoggerTypeInfo = 2 /**< tipo info */
} MytuiLoggerType;


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
 * @param tipo de error
 * @param formato que imprimer
 * @param parametros que se agregaran al formato
 */
void print_line_log(MytuiLoggerType mytuiLoggerType, const char *msg, ...);


#endif
