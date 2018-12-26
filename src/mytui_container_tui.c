#include "mytui_container_tui.h"
/**
 * @brief lista para trasformación del buffer.
 *
     * Esta estructura maneja el buffer para pintado de la terminal.
*/
struct mytuiContainer{
    int x; /**< posición x MytuiContainer#x. */
    int y; /**< posición y MytuiContainer#y. */
    int w; /**< ancho MytuiContainer#w. */
    int h; /**< posición y NodeTranformation#y. */
    int fg; /**< Color de letra NodeTranformation#fg. */
    int bg; /**< Color de letra NodeTranformation#bg. */
    bool decoration; /**< Si posee decoracion NodeTranformation#decoration. */
    ContainerTypes type;
};

void mytui_inicialize_container(MytuiContainer **stance, MytuiContainerParam param)
{
    if(*stance != NULL){
        print_error("mytui_inicialize_container: el container debe ser null");
    }
    *stance = (MytuiContainer*)malloc(sizeof(MytuiContainer));
    (*stance)->bg = param.bg;
    (*stance)->x = param.x;
    (*stance)->y = param.y;
    (*stance)->h = param.h;
    (*stance)->w = param.w;
    (*stance)->type = param.type;
    (*stance)->decoration = param.decoration;
}


void update_MytuiContainer(MytuiContainer *container)
{
    if(container == NULL){
        print_error("update_MytuiContainer: "
            "No se puede inicializar un Entry en NULL");
    }
    NodeTranformation *node = NULL;

    if(container->type == MYTUI_CONTAINER_ROOT){
        struct InfoTerm infoTerm = get_info_term();
        container->x = 0;
        container->y = 0;
        container->w =infoTerm.width;
        container->h =infoTerm.height;
    }

    for(int i = container->y; i < (container->h + container->y) ; i++){
        for(int j = container->x; j < (container->w + container->x); j++){
            if(container->decoration == true){
                if(i == container->y || i == (container->h + container->y) - 1){
                    //caracter de la decoracion
                    uint32_t decoration = ' ';

                    //iconos de cerrar agrandar para la ventana

                    if(container->type == MYTUI_CONTAINER_WIN &&
                        (container->w + container->x) - 2 == j &&
                        i == container->y  ){
                        decoration = 0x2591;
                    }else if(container->type == MYTUI_CONTAINER_WIN &&
                        (container->w + container->x) - 3 == j &&
                        i == container->y){
                        decoration = 0x2591;
                    }else if(j == container->x && i == container->y){
                        //┌
                        decoration = 0x250C;
                    }else if((container->w + container->x) - 1 == j &&
                        i == container->y){
                        //┐
                        decoration = 0x2510;
                    }else if(j == container->x &&
                        (container->h + container->y) - 1){
                        //└
                        decoration = 0x2514;
                    }else if((container->w + container->x) - 1 == j &&
                        (container->h + container->y) - 1){
                        //┘
                        decoration = 0x2518;
                    }else{
                        //─
                        decoration = 0x2500;
                    }
                    nodeTranformation_add(&node, j, i, 12,16, decoration);
                }else if(j == container->x || j ==
                        (container->w + container->x)- 1){
                    //'|'
                    nodeTranformation_add(&node, j, i, 12,16, 0x2502);
                }else{
                    nodeTranformation_add(&node, j, i, 12,MYTUI_COLOR_DEFAULT, ' ');
                }
            }else{
                nodeTranformation_add(&node, j, i, 12,MYTUI_COLOR_DEFAULT, ' ');
            }
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}

void free_mytui_container(MytuiContainer **stance){
    if (*stance != NULL) {
        free(*stance);
    }
}
