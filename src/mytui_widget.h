#ifndef __MYTUI_WIDGET_H__
#define __MYTUI_WIDGET_H__

#include "mytui_widget_types.h"

#include "mytui_color.h"
#include "mytui.h"
#include "mytui_config.h"
#include "mytui_config.h"
#include "mytui_buffer.h"


/**
 * @brief lista de buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct MiTuiWidget{
    int x;
    int y;
    int w;
    int h;
    int bc;
    WidgetTypes type;
}MiTuiWidget;

void init_MyTuiWidgetEntry(MiTuiWidget ** widget, int x, int y, int w, int h, int bc);

void update_MyTuiWidgetEntry(MiTuiWidget *widget);


void free_MyTuiWidgetEntry(MiTuiWidget **widget);

#endif
