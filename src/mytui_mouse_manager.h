#ifndef __MYTUI_MOUSE_MANAGER__
#define __MYTUI_MOUSE_MANAGER__

#include "mytui_widget.h"
#include "mytui_animation.h"

/**
 * @brief enumeración de widget en el core.
 *
 * enum que posee los distintos widget de core.
 * Los de tipo Shadow son eventos con callback null internos para ejemplo
 *  colocar el widget en activo
 */
typedef enum {
    mytuiEventClickPrincipal = 1,
    mytuiEventShadow = 2
} EventType;

/**
 * @brief lista para trasformación del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
typedef struct mytuiStackMouseEvent {
    void (*call_back)();
    EventType eventType;
    struct MiTuiWidget *widget;
    struct mytuiStackMouseEvent *next;
} MytuiStackMouseEvent;

/**
* agrega un evento de click a un widget
* @param callback del evento
* @param tipo de event
* @param widget que va asociado el evento
* @return verdadero si se pudo insertar
*/
bool add_mytui_event_listener(void (*call_back)(), EventType eventType, struct MiTuiWidget *widget);

/**
* borra un listener asociado a un widget, coinciden los dos parámetros los eliminas
* @param widget que asocia el event
* @param tipo de evento
*/
void delete_mytui_listener( struct MiTuiWidget *widget, EventType eventType);

/**
* borra todo los eventos este no libera las funciones ni los widget
*/
void delete_mytui_listener_all();

void mouse_manager_event_fire(int32_t x, int32_t y);



#endif
