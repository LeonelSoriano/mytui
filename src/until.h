/** @file until.h
*  @ingroup Conf
*  @brief funciones varias de apoyo
*  @date 28-11-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __UNTIL__
#define __UNTIL__

#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>


#include "mytui_color.h"
#include "mytui_cmd.h"


//#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))
//#define SUM(...)  (sum(NUMARGS(__VA_ARGS__), __VA_ARGS__))

/**
* informacion de la terminal
*/
struct InfoTerm{
    unsigned int width;
    unsigned int height;
};

/**
 * llena la inormacion de la terminal
 * @return struct InfoTerm
 */
struct InfoTerm get_info_term();

/**
 * ejecuta un comando del so sin reportarlo
 * @param comando a ejecutar
 */
void run_cmd_silent(const char *cmd);

/**
 * imprimer error
 * @param mensaje en formato stdio
 * @patam parametros variables
*/
void print_error( const char *msg, ...);

/**
 * imprimero un mensaje de info con fecha
 * @param mensaje en informato stdio
 * @param parametro variables
 */
void print_info( const char *msg, ...);

/**
 * verificasi un archivo existe
 * @param path del archivo
 * @return true si existe
 */
bool exist_file(const char* path);

/**
 * consige el folder home del so
 * @return path home
 */
const char* get_home_folder();

/**
 * lee el archibo de conf y lo coloca en memoria
 * @return hash que posee la configuracion
 */
//GHashTable* read_file_conf();

/**
 * verifica si todos los caracteres de un string son enteros
 * @param cadena de texto a verificar
 * @return verdadero si todos son enteros
 */
bool strIsInt(const char *str);


/**
 * verififica si el el valor es un valor(int) por defecto por ahora -1
 * @param valor a verificar
 * @return valor por defecto
 */
int isDefaulValueInt(int value);


#endif
