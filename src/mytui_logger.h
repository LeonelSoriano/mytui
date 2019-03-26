/** @file mytui_logger.h
 *  @ingroup Logger
 *  @brief base de sistema de logger
 *  @date 26-03-2019
 *  @author leonelsoriano3@gmail.com
 */
#ifndef __MYTUI_LOGGER_CONF_H__
#define __MYTUI_LOGGER_CONF_H__

#include "until.h"
#include <dirent.h>

/**
 * @brief enumeración de tipo de mensajes en el logger.
 *
 */
typedef enum {
    MytuiLoggerTypeError = 0, /**< tipo error */
    MytuiLoggerTypeInfo = 1, /**< tipo info */
    MytuiLoggerTypeWarning = 2 /**< tipo advertencia */
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
