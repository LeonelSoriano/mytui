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


    if(stackMouseEvent == NULL){
        return;
    }
        MytuiStackMouseEvent *validate_stackMouseEvent = stackMouseEvent;
        while (validate_stackMouseEvent != NULL) {
            /*if (validate_stackMouseEvent->widget == widget &&
                validate_stackMouseEvent->eventType == eventType) {
            }*/


            switch (validate_stackMouseEvent->eventType) {
                case mytuiEventClickPrincipal: /*mytuiEventClickPrincipal*/
                    if(validate_stackMouseEvent->widget->type ==  mytuiButton){


                        if((y >= validate_stackMouseEvent->widget->y &&
                            y <=  validate_stackMouseEvent->widget->y +
                            validate_stackMouseEvent->widget->h) &&
                             (x >= validate_stackMouseEvent->widget->x &&
                             x <=  validate_stackMouseEvent->widget->x +
                             validate_stackMouseEvent->widget->w)){


                            change_active_miTuiWidget(validate_stackMouseEvent->widget);

                            //animation del boton al pulsar
                            MytuiAnimation *animation = init_MytuiAnimation( validate_stackMouseEvent->widget);
                            add_step_MytuiAnimation(&animation, mytuiAnimationMove,
                                (double[]){-1, -1, 3, 4},0.2);
                            add_step_MytuiAnimation(&animation, mytuiAnimationMove,
                                (double[]){1, 1, 3, 4},0.2);

                            update_mytuiAnimation(&animation);



                            //update_MyTuiWidget(validate_stackMouseEvent->widget);
                            free_MytuiAnimation(&animation);
                            // end de animacion del boton


                            validate_stackMouseEvent->call_back();
                        }



                    }else if(validate_stackMouseEvent->widget->type == mytuiLabel){


                        if((y >= validate_stackMouseEvent->widget->y &&
                            y <=  validate_stackMouseEvent->widget->y +
                            validate_stackMouseEvent->widget->h) &&
                             (x >= validate_stackMouseEvent->widget->x &&
                             x <=  validate_stackMouseEvent->widget->x +
                             validate_stackMouseEvent->widget->w)){

                            validate_stackMouseEvent->call_back();

                        }
                    }

                    break;
            }


            validate_stackMouseEvent = validate_stackMouseEvent->next;
        }


}

