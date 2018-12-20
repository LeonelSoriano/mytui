#ifndef __MYTUI_CONTAINER_TUI_H__
#define __MYTUI_CONTAINER_TUI_H__

typedef enum {
    root = 1 /**< Componente vacio WidgetTypes#entry. */
}ContainerTypes;

/**
 * @brief lista para tranformacion del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
*/
typedef struct MytuiContainer{
    int x; /**< posicion x MytuiContainer#x. */
    int y; /**< posicion y MytuiContainer#y. */
    int w; /**< ancho MytuiContainer#w. */
    int h; /**< posicion y NodeTranformation#y. */
    int fg; /**< Color de letra NodeTranformation#fg. */
    int bg; /**< Color de letra NodeTranformation#bg. */
    bool decoration;
    ContainerTypes type;
}MytuiContainer;



#endif
