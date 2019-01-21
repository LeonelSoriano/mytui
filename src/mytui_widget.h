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

#include <string.h>

/**
 * @brief lista de buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct MiTuiWidget {
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

MiTuiWidget *init_MyTuiWidgetEntry(int x, int y, int w, int h, int bc);

MiTuiWidget *init_MyTuiWidgetLabel(char *text, int x, int y, int w, int h, int bc, int fc);

void update_MyTuiWidget(MiTuiWidget *widget);

void free_MyTuiWidget(MiTuiWidget **widget);

#endif
