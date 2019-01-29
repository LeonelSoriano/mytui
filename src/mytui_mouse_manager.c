#include "mytui_mouse_manager.h"

static MytuiStackMouseEvent *stackMouseEvent = NULL;

bool add_mytui_event_listener(void (*call_back)(), EventType eventType, struct MiTuiWidget *widget)
{
    if (stackMouseEvent == NULL) {
        stackMouseEvent = (MytuiStackMouseEvent *)malloc(sizeof(MytuiStackMouseEvent));
        stackMouseEvent->call_back = call_back;
        stackMouseEvent->eventType = eventType;
        stackMouseEvent->widget = widget;
        stackMouseEvent->next = NULL;
    } else {

        // revisar si ya existe esta combinacion
        MytuiStackMouseEvent *validate_stackMouseEvent = stackMouseEvent;
        while (validate_stackMouseEvent != NULL) {
            if (validate_stackMouseEvent->widget == widget &&
                validate_stackMouseEvent->eventType == eventType) {
                return false;
            }

            validate_stackMouseEvent = validate_stackMouseEvent->next;
        }

        MytuiStackMouseEvent *new_stackMouseEvent =
            (MytuiStackMouseEvent *)malloc(sizeof(MytuiStackMouseEvent));
        new_stackMouseEvent->call_back = call_back;
        new_stackMouseEvent->eventType = eventType;
        new_stackMouseEvent->widget = widget;

        MytuiStackMouseEvent *tmp_stackMouseEvent = stackMouseEvent;
        new_stackMouseEvent->next = tmp_stackMouseEvent;
        stackMouseEvent = new_stackMouseEvent;
    }
    return true;
}

void delete_mytui_listener(struct MiTuiWidget *widget, EventType eventType)
{
    if (widget == NULL || stackMouseEvent == NULL) {
        return;
    }
    MytuiStackMouseEvent *tmpStackMouseEvent = stackMouseEvent;
    MytuiStackMouseEvent *prevStackMouseEvent = NULL;

    while (tmpStackMouseEvent != NULL) {

        if (tmpStackMouseEvent->widget == widget && tmpStackMouseEvent->eventType == eventType) {

            if (prevStackMouseEvent != NULL) {
                prevStackMouseEvent->next = tmpStackMouseEvent->next;
                free(tmpStackMouseEvent);
                tmpStackMouseEvent = NULL;
            } else {
                free(stackMouseEvent);
                stackMouseEvent = NULL;
            }
            break;
        }
        prevStackMouseEvent = tmpStackMouseEvent;
        tmpStackMouseEvent = tmpStackMouseEvent->next;
    }
}

void delete_mytui_listener_all()
{
    if (stackMouseEvent == NULL) {
        return;
    }

    while (stackMouseEvent != NULL) {
        MytuiStackMouseEvent *tmpStackMouseEvent = stackMouseEvent->next;
        free(stackMouseEvent);
        stackMouseEvent = NULL;
        stackMouseEvent = tmpStackMouseEvent;
    }
}



void mouse_manager_event_fire(int32_t x, int32_t y){
    
}


