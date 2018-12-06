/** @file mytui_buffer.h
*  @ingroup Conf
*  @brief bufffer de dibujado de la pantalla
*  @date 02-12-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __MYTUI_BUFFER_H__
#define __MYTUI_BUFFER_H__

#include <stdbool.h>

#include "../termbox/build/usr/include/termbox.h"

#include "until.h"

/**
 * @brief lista de buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct NodeBufer{
    int fg; /**< Color de letra NodeBufer#fg. */
    int bg; /**< Color de fondo NodeBufer#bg. */
    bool update; /**< Verifica si se actualizara o no NodeBufer#update.*/ 
    struct NodeBufer *next; /**< proximo nodo NodeBufer#next.*/
}NodeBufer;

typedef struct NodeTranformation{
    int x;
    int y;
    int fg;
    int bg;
   struct NodeTranformation *next;
}NodeTranformation;

/**
 * inicia el buffer de pintado de la terminal
 * @param structura de nodos del buffer
 */
void init_buffer(NodeBufer **nodeBufer);

/**
 * libera memoria del buffer de pintado de la terminal
 * @param structura de nodos del buffer
 */
void free_buffer(NodeBufer **nodeBufer);

/**
 * pinta en pantalla por el buffer pasado
*/
void screen_manager(NodeBufer **nodeBufer);

void reevaluete_screen_manager(NodeBufer **nodeBufer);

void nodeTranformation_init(NodeTranformation **nodeTranformation);

void nodeTranformation_add(NodeTranformation **nodeTranformation);

void nodeTranformation_free(NodeTranformation **nodeTranformation);

#endif
