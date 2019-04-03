/** @file mytui.h
*  @ingroup Conf
*  @brief inicio y cierre de libreria
*  @date 28-11-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __MYTUI__
#define __MYTUI__

#include "mytui_config.h"

#include "../termbox/build/usr/include/termbox.h"


#include "mytui_logger.h"
#include "mytui_animation.h"
#include "mytui_buffer.h"
#include "mytui_widget.h"
#include "mytui_container_tui.h"
#include "mytui_mouse_manager.h"
#include "mytui_active_manager.h"

/**
 * global para administrar el buffer de pantalla
 */
NodeBufer *nodeBufer;

ConfMap *_confMap;

/**
 * tiene la implementacion de los click y otras cosas
 * @see init_mytui
 */
void update_termbox();

/**
 *  inicio de la libreria
 */
void init_mytui();

/**
* liberacion de recursos
*/
void end_mytui();


#endif
