/** @file until.h
 *  @ingroup Conf
 *  @brief widget de mytui
 *  @date 06-01-2019
 *  @author leonelsoriano3@gmail.com
 */
#ifndef __MYTUI_WIDGET_H__
#define __MYTUI_WIDGET_H__

#include "mytui_widget_types.h"

#include "mytui.h"
#include "mytui_buffer.h"
#include "mytui_color.h"
#include "mytui_config.h"
#include "mytui_container_tui.h"

#include <string.h>

/**
 * @brief lista de buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
 typedef  struct MiTuiWidget {
    int x;
    int y;
    int w;
    int h;
    int bc;      /**< color backgound MiTuiWidget#bc. */
    int fc;      /**< color fore MiTuiWidget#bc. */
    void *extra; /**< structuras que guardan valores unicos de los widget
                        MiTuiWidget#especific. */
    WidgetTypes type;
} MiTuiWidget;

typedef struct MiTuiWidgetExtraLabel {
    char *text;
} MiTuiWidgetExtraLabel;


typedef struct MiTuiWidgetExtraButton {
    char *text;
    int shadow;
    bool shadowActive;
    int active;
    int fgActive;

} MiTuiWidgetExtraButton;


MiTuiWidget *init_MyTuiWidgetEntry(int x, int y, int w, int h, int bc);

/**
* inicia un widget como label
* @param texto del label
* @param posición en x
* @param posición en y
* @param ancho del label
* @param alto del label
* @param color de fondo
* @param color de el texto
* @return widget inicializado como un label
*/
MiTuiWidget *init_MyTuiWidgetLabel(char *text, int x, int y, int w, int h, int bc, int fc);


/**
* inicia un widget como un button
* @param texto del label
* @param posición en x
* @param posición en y
* @param ancho del label
* @param alto del label
* @param color de fondo
* @param color de el texto
* @param color de la sombra si es -1 no tendrá sombra
* @return widget inicializado como un label
*/
MiTuiWidget* init_MyTuiWidgetButton(char *text, int x, int y, int w, int h,int bc, int fc, int shadow);

void update_MyTuiWidget(MiTuiWidget *widget);

void free_MyTuiWidget(MiTuiWidget **widget);

/**
* borra de la pantalla un anterior widget
* @param el widget que se eliminara
* @param el container que posee al widget actual
*/

void clean_MyTuiWidget(MiTuiWidget *widget, struct mytuiContainer *stance);


#endif
