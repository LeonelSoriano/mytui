#include "mytui_container_tui.h"
/**
 * @brief lista para trasformación del buffer.
 *
     * Esta estructura maneja el buffer para pintado de la terminal.
*/
struct mytuiContainer{
    int x; /**< posición x mytuiContainer#x. */
    int y; /**< posición y mytuiContainer#y. */
    int w; /**< ancho mytuiContainer#w. */
    int h; /**< altura mytuiContainer#h. */
    int bg; /**< Color de letra mytuiContainer#bg. */
    bool decoration; /**< Si posee decoración mytuiContainer#decoration. */
    int border; /**< Color del borde mytuiContainer#border. */
    int closeColor; /**< Color botón de cerrar mytuiContainer#coloseColor. */
    int minimizeColor; /**< color del icono de minimizar mytuiContainer#minimize.*/
    ContainerTypes type; /**<typo de contenedor mytuiContainer#type. */
    struct ChildContainer *childContainer;
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
    (*stance)-> border = param. border;
    (*stance)->type = param.type;
    (*stance)->closeColor = param.closeColor;
    (*stance)->minimizeColor = param.minimizeColor;
    (*stance)->decoration = param.decoration;
}


void update_MytuiContainer(MytuiContainer *container)
{
    if(container == NULL){
        print_error("update_MytuiContainer: "
            "No se puede inicializar un Entry en NULL");
    }
    NodeTranformation *node = NULL;


    //evaluacion del container bg
    char* container_bg;
    if(container->bg < 0){
        container_bg = resolve_value(_confMap, "container.bg", NULL);
    }else{
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->bg);
        container_bg = resolve_value(_confMap, "container.bg", buffer_str);
    }
    if(!strIsInt(container_bg)){
         print_error("update_MytuiContainer: valor container.bg debe ser entero");
    }
    unsigned int container_bg_int = atoi(container_bg);
    //end evaluacion del container bg

    //evaluacion del container close
    char* container_close_color;
    if(container->closeColor < 0){
        container_close_color = resolve_value(_confMap, "container.close", NULL);
    }else{
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->bg);
        container_close_color =
            resolve_value(_confMap, "container.close", buffer_str);
    }
    if(!strIsInt(container_close_color)){
         print_error("update_MytuiContainer: valor"
            "container.close debe ser entero");
    }
    unsigned int container_close_color_int = atoi(container_close_color);
    //end evaluacion del container close color

    //evaluacion del container close
    char* container_minimize_color;
    if(container->minimizeColor < 0){
         container_minimize_color = resolve_value(_confMap,
            "container.minimize", NULL);
    }else{
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->minimizeColor);
        container_close_color =
            resolve_value(_confMap, "container.minimize", buffer_str);
    }
    if(!strIsInt( container_minimize_color)){
         print_error("update_MytuiContainer: valor"
            "container.minimize debe ser entero");
    }
    unsigned int container_minimize_color_int = atoi(container_minimize_color);
    //end evaluacion del container close color


    //evaluacion del container border
    char* container_border;
    if(container->border < 0){
        container_border = resolve_value(_confMap, "container.border", NULL);
    }else{
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->border);
        container_border = resolve_value(_confMap, "container.border", buffer_str);
    }
    if(!strIsInt(container_border)){
         print_error("update_MytuiContainer: valor container.bg debe ser entero");
    }
    unsigned int container_border_int = atoi(container_border);
    //end evaluacion del container border


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

                    //para agregar extra colores como para el cerrar manimizar
                    unsigned int resolution_extra_color = container_bg_int;

                    //iconos de cerrar agrandar para la ventana
                    if(container->type == MYTUI_CONTAINER_WIN &&
                        (container->w + container->x) - 2 == j &&
                        i == container->y  ){
                        decoration = 0x2591;
                        resolution_extra_color =container_close_color_int;

                    }else if(container->type == MYTUI_CONTAINER_WIN &&
                        (container->w + container->x) - 3 == j &&
                        i == container->y){
                        decoration = 0x2591;
                        resolution_extra_color = container_minimize_color_int;

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
                    nodeTranformation_add(&node, j, i, resolution_extra_color,
                        container_border_int, decoration);

                }else if(j == container->x || j ==
                        (container->w + container->x)- 1){
                    //'|'
                    nodeTranformation_add(&node, j, i,
                        container_bg_int,container_border_int, 0x2502);
                }else{
                    nodeTranformation_add(&node, j, i,
                        container_bg_int,MYTUI_COLOR_DEFAULT, ' ');
                }
            }else{
                nodeTranformation_add(&node, j, i, container_bg_int,
                    MYTUI_COLOR_DEFAULT, ' ');
            }
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}

void free_mytui_container(MytuiContainer **stance){
    if (*stance != NULL) {
        while((*stance)->childContainer  != NULL){
            print_error("error");
            ChildContainer *tmpChildContainer = (*stance)->childContainer->next;
            free((*stance)->childContainer);
            (*stance)->childContainer = tmpChildContainer;
        }
        free(*stance);
    }
}


void add_ChildContainer(MytuiContainer **stance){
    if((*stance)->childContainer == NULL){
        (*stance)->childContainer =
            (ChildContainer*)malloc(sizeof(ChildContainer));
        (*stance)->childContainer->next = NULL;
    }else{
        ChildContainer *tmp_old = (*stance)->childContainer;

        ChildContainer *tmpChildContainer =
            (ChildContainer*)malloc(sizeof(ChildContainer));

         (*stance)->childContainer = tmpChildContainer;
        (*stance)->childContainer->next = tmp_old;

    }
}

void add_childContainerWidget(ChildContainer **childContainer,
    float margin_left, float margin_right, float margin_bottom, float margin_top,
    MiTuiWidget **miTuiWidget){
    if((*childContainer) == NULL){
        print_error("add_childContainerWidget: childContainerWidget no puede"
            " ser null");
    }

    if((*miTuiWidget) == NULL){
        print_error("add_childContainerWidget: miTuiWidget no puede ser NULL");
    }

    if((*childContainer)->childContainerWidget == NULL){
        ChildContainerWidget *containerWidget =
            (ChildContainerWidget*)malloc(sizeof(ChildContainerWidget));
        containerWidget->margin_bottom = margin_bottom;
        containerWidget->margin_left = margin_left;
        containerWidget->margin_top = margin_top;
        containerWidget->margin_bottom = margin_bottom;
        containerWidget->next = NULL;
        containerWidget->widget = (*miTuiWidget);
        (*childContainer)->childContainerWidget = containerWidget;
    }else{

        ChildContainerWidget* tmp_old = (*childContainer)->childContainerWidget;

        ChildContainerWidget *tmpContainerWidget =
            (ChildContainerWidget*)malloc(sizeof(ChildContainerWidget));
        tmpContainerWidget->margin_bottom = margin_bottom;
        tmpContainerWidget->margin_left = margin_left;
        tmpContainerWidget->margin_top = margin_top;
        tmpContainerWidget->margin_bottom = margin_bottom;
        tmpContainerWidget->widget = (* miTuiWidget);

        (*childContainer)->childContainerWidget = tmpContainerWidget;
        (*childContainer)->childContainerWidget->next = tmp_old;
    }

}

