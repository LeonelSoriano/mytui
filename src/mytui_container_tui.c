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
#include <locale.h>

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


setlocale(LC_CTYPE, "");

    for(int i = container->y; i < (container->h + container->y) ; i++){
        for(int j = container->x; j < (container->w + container->x); j++){
            if(container->decoration == true){
                if(i == 0){
                    //nodeTranformation_add(&node, j, i, 12,16, 0x2605);
                    if(j == container->x){
                        nodeTranformation_add(&node, j, i, 12,16, 's');
                    }else if((container->w + container->x) - 1 == j){
                        nodeTranformation_add(&node, j, i, 12,16, 'x');
                    }else{
                        nodeTranformation_add(&node, j, i, 12,16, 0x2500);
                    }

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
