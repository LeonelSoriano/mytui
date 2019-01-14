#ifndef __MYTUI_CONTAINER_TUI_H__
#define __MYTUI_CONTAINER_TUI_H__

#include <stdlib.h>
#include <stdbool.h>

#include "mytui_widget.h"
#include "mytui.h"
#include "mytui_config.h"
#include "mytui_buffer.h"

/**
* @brief numerador de typo de container.
*
*/
typedef enum {
    MYTUI_CONTAINER_ROOT = 1, /**< Componente vació ContainerTypes#MYTUI_CONTAINER_ROOT. */
    MYTUI_CONTAINER_WIN = 2 /**< Componente tipo ventana ContainerTypes#MYTUI_CONTAINER_WIN. */
}ContainerTypes;

typedef struct mytuiContainer MytuiContainer;

/**
* @brief contenedores hijos.
*
* estructura que contiene los hijos de los contenedores
*/
typedef struct ChildContainer{
    int len;
    struct ChildContainer  *next;
    struct childContainerWidget *childContainerWidget;
}ChildContainer;

/**
* @brief lista que posee los widget.
*
* estructura que contiene los hijos de los contenedores
*/
typedef struct childContainerWidget{
    float margin_left; /**< margen derecho este es para un especifico childContainerWidget#margin_left. */
    float margin_right;
    float margin_bottom;
    float margin_top;
    struct MiTuiWidget* widget;
    struct childContainerWidget *next;
}ChildContainerWidget;

typedef struct MytuiContainerParam{
    int bg;
    int border;
    int x;
    int y;
    int w;
    int h;
    bool decoration;
    int closeColor;
    int minimizeColor;
    ContainerTypes type;
}MytuiContainerParam;


#define INIT_MYTUI_CONTAINER(X) MytuiContainerParam  X = {.bg = -1, .border = -1,\
    .x = -1,.y = -1, .w = -1, .h = -1,.decoration = false, .closeColor = -1,\
    .minimizeColor=-1, .type = MYTUI_CONTAINER_ROOT}

/**
* inicializa un container
* @param referencia al container
* @param parámetros que se pasaran al container como inicio
*/
void mytui_inicialize_container(MytuiContainer **stance, MytuiContainerParam param);

/**
* método de actualización del container
* @param referencia del container
* @return valor por defecto
*/
void update_MytuiContainer(MytuiContainer *cotainer);

/**
 * método que libera la memoria de un container
 * @param referencia del container
 */
void free_mytui_container(MytuiContainer **stance);

/**
 * método que inicializa un ChildContainer
 * @param referencia del ChildContainer
 */
void add_ChildContainer(MytuiContainer **stance);

/**
* agrega un widget a un child container el free para este método lo tiene el
* free container el cual libera los recursos de manera dinámica
* @param referencia al container que posee el child container
* @param margen derecho en porcentaje
* @param margen izquierdo en porcentaje
* @param margen inferior en pixeles
* @param margen superior en pixeles
* @param widget que se agregara al container
*/
void add_childContainerWidget(MytuiContainer **mytuiContainer,
    float margin_left, float margin_right, float margin_bottom, float margin_top,
    struct MiTuiWidget **miTuiWidget);


/**
* actualiza para dibujar todos los widget en el child
* @param contenedor
*/
void update_MytuiContainer_childContainer(MytuiContainer *container);


/**
 * método que inicializa un ChildContainer
 * @param referencia del ChildContainer
 * @return valor por defecto
 */
#endif
