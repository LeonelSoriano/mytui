/** @file until.h
*  @ingroup Conf
*  @brief funciones varias de apoyo
*  @date 28-11-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __UNTIL_H__
#define __UNTIL_H__

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
#include "mytui_logger.h"


//#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))
//#define SUM(...)  (sum(NUMARGS(__VA_ARGS__), __VA_ARGS__))

/**
* informacion de la terminal
*/
struct InfoTerm{
    unsigned int width;
    unsigned int height;
};

/* nombre de archivos y folder usados */
#ifdef __MINGW32__
//static const char *SEPARATOR_FOLDER = "\\";
#else
static const char  __attribute__((unused)) *SEPARATOR_FOLDER = "/";
#endif

static const char __attribute__((unused)) *CONF_FONDER = ".config";
static const char __attribute__((unused)) *TUI_FOLDER_CONF = "mytui";

static const char __attribute__((unused)) *TUI_FOLDER_LOG = "log";

static const char __attribute__((unused)) *CONF_FILE_NAME = "init.conf";


/**
 * consigue elk path de toda la conf de mytui
 * @return el path de mytui
 */
const char *get_file_mytui_path();

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


int dump(void *myStruct, long size);

/**
 * busca una palabra y devuelve su indeice 
 * @param string donde se buscara
 * @param palabra a buscar
 * @return indice inical donde se encuentra la palabra
 */
int search(char str[], char word[]);

/**
 * elimina una plabra deontro de un string
 * @param string donde se buscara
 * @param palabra que se removera
 * @return devuelve 1 si consigue la plabra, 0 si no puede eliminar o no se euentra
 */
int delete_word(char str[], char word[]);


/**
 * pasa la informacion de  un archivo de texto a otro y vacia el primero
 * @param path del archivo de origen
 * @param path al nuevo archivo
 * @return devuelve verdadero si no hay errores
 */
bool copy_file(const char*origin_file, const char* new_file);

#endif
