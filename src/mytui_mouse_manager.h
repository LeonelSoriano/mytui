#ifndef __MYTUI_MOUSE_MANAGER__
#define __MYTUI_MOUSE_MANAGER__

#include "mytui_widget.h"

/**
 * @brief enumeracion de widget en el core.
 *
 * Enum que posee los distintos widget de core.
 */
typedef enum {
    mytuiEventTypePrincipal = 1,
} EventType;

/**
 * @brief lista para tranformacion del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct mytuiStackMouseEvent {
    void (*call_back)();
    EventType eventType;
    MiTuiWidget *widget;
    struct mytuiStackMouseEvent *next;
} MytuiStackMouseEvent;

void add_mytui_event_listener(void (*call_back)(), EventType eventType, MiTuiWidget *widget);

void delete_mytui_listener(MiTuiWidget *widget, EventType eventType);

#endif
