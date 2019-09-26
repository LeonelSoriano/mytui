/** @file mytui_active_manager.h
*  @ingroup managerActive
*  @brief manager el item actual
*  @date 02-04-2018
*  @author leonelsoriano3@gmail.com
*/
#ifndef __MYTUI_ACTIVE_MANAGER_H__
#define  __MYTUI_ACTIVE_MANAGER_H__

#include "mytui_widget.h"

/**
 * @brief lista para trasformación del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
struct MytuiActiveWidget {
    struct MiTuiWidget *miTuiWidget;    /**< posición x MytuiActiveWidget#miTuiWidget. */
    int bc;      /**< before color backgound MytuiActiveWidget#bc. */
    int fc;      /**< before color fore MytuiActiveWidget#bc. */
};
typedef struct MytuiActiveWidget  MytuiActiveWidget;

/**
 *  @brief cambia el widget activo en mytui
 *  @param Widget que sera el actual activo
 */
void change_active_miTuiWidget(struct MiTuiWidget *miTuiWidget);

/**
 *  @brief accion sobre un widget activo
 *  @param uint16_t char de tecla pulsada
 *  @param uint16_t codigo de tecla pulsada
 */
void action_active_miTuiWidget(uint16_t ch, uint16_t key);

extern void delete_active_miTuiWidget();


#endif
