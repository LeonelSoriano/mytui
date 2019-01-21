#ifndef __MYTUI_MOUSE_MANAGER__
#define __MYTUI_MOUSE_MANAGER__

#include "mytui_widget.h"



/**
 * @brief enumeracion de widget en el core.
 *
 * Enum que posee los distintos widget de core.
 */
typedef enum {
    eventTypePrincipal = 1,
}EventType;



/**
 * @brief lista para tranformacion del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct stackMouseEvent{
    void (*call_back)();
    EventType eventType;
    MiTuiWidget *widget;
    struct stackMouseEvent *next;
}StackMouseEvent;


#endif
