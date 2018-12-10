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
#include "./mytui_color.h"

/**
 * @brief lista de buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct NodeBufer{
    int fg; /**< Color de letra NodeBufer#fg. */
    int bg; /**< Color de fondo NodeBufer#bg. */
    bool update; /**< Verifica si se actualizara o no NodeBufer#update.*/
    char ch;
    struct NodeBufer *next; /**< proximo nodo NodeBufer#next.*/
}NodeBufer;

/**
 * @brief lista para tranformacion del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct NodeTranformation{
    int x; /**< Color de letra NodeTranformation#x. */
    int y; /**< Color de letra NodeTranformation#y. */
    int fg; /**< Color de letra NodeTranformation#fg. */
    int bg; /**< Color de letra NodeTranformation#bg. */
    char ch;
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

/**
 * re imprimer la pantalla apartir de un *NodeBuffer
 */
void init_screen_manager(NodeBufer **nodeBufer);

/**
 * inicia un nodeTranformation lo coloca a NULL
 * @param NodeTranformation
 */
void nodeTranformation_init(NodeTranformation **nodeTranformation);

void nodeTranformation_add(NodeTranformation **nodeTranformation, int x, int y, int fg, int bg);

void nodeTranformation_free(NodeTranformation **nodeTranformation);

void node_bufffer_vs_tranformator(NodeBufer **nodeBufer, NodeTranformation *nodeTranformation);

#endif
