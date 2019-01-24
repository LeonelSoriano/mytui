#include "mytui_mouse_manager.h"

static MytuiStackMouseEvent *stackMouseEvent = NULL;

void add_mytui_event_listener(void (*call_back)(), EventType eventType, MiTuiWidget *widget)
{
    if (stackMouseEvent == NULL) {
        stackMouseEvent = (MytuiStackMouseEvent *)malloc(sizeof(MytuiStackMouseEvent));
        stackMouseEvent->call_back = call_back;
        stackMouseEvent->eventType = eventType;
        stackMouseEvent->widget = widget;
        stackMouseEvent->next = NULL;
    } else {

        MytuiStackMouseEvent *new_stackMouseEvent =
            (MytuiStackMouseEvent *)malloc(sizeof(MytuiStackMouseEvent));
        new_stackMouseEvent->call_back = call_back;
        new_stackMouseEvent->eventType = eventType;
        new_stackMouseEvent->widget = widget;

        MytuiStackMouseEvent *tmp_stackMouseEvent = stackMouseEvent;
        new_stackMouseEvent->next = tmp_stackMouseEvent;
        stackMouseEvent = new_stackMouseEvent;
    }
}

void delete_mytui_listener(MiTuiWidget *widget, EventType eventType)
{
    if (widget == NULL || stackMouseEvent == NULL) {
        return;
    }
    MytuiStackMouseEvent *tmpStackMouseEvent = stackMouseEvent;
    MytuiStackMouseEvent *prevStackMouseEvent = NULL;


    while (tmpStackMouseEvent != NULL) {

        if (tmpStackMouseEvent->widget == widget && tmpStackMouseEvent->eventType == eventType) {
            print_error("eliminado");


            break;
        }
        prevStackMouseEvent = tmpStackMouseEvent;
        tmpStackMouseEvent = tmpStackMouseEvent->next;
    }
}
