#ifndef __MYTUI_CONTAINER_TUI_H__
#define __MYTUI_CONTAINER_TUI_H__

#include <stdlib.h>
#include <stdbool.h>

#include "mytui.h"
#include "mytui_config.h"
#include "mytui_buffer.h"

typedef enum {
    MYTUI_CONTAINER_ROOT = 1, /**< Componente vacio Container#root. */
    win = 2
}ContainerTypes;

typedef struct mytuiContainer MytuiContainer;


typedef struct MytuiContainerParam{
    int bg;
    int x;
    int y;
    int w;
    int h;
    bool decoration;
    ContainerTypes type;
}MytuiContainerParam;

#define INIT_MYTUI_CONTAINER(X) MytuiContainerParam  X = {.bg = 255, .x = -1,\
    .y = -1, .w = -1, .h = -1, .decoration = false, .type = MYTUI_CONTAINER_ROOT}

void mytui_inicialize_container(MytuiContainer **stance, MytuiContainerParam param);


void update_MytuiContainer(MytuiContainer *cotainer);

void free_mytui_container(MytuiContainer **stance);
#endif
