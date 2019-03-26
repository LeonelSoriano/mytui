#include "mytui_container_tui.h"
/**
 * @brief lista para trasformación del buffer.
 *
 * Esta estructura maneja el buffer para pintado de la terminal.
 */
struct mytuiContainer {
    int x;               /**< posición x mytuiContainer#x. */
    int y;               /**< posición y mytuiContainer#y. */
    int w;               /**< ancho mytuiContainer#w. */
    int h;               /**< altura mytuiContainer#h. */
    int bg;              /**< Color de letra mytuiContainer#bg. */
    bool decoration;     /**< Si posee decoración mytuiContainer#decoration. */
    int border;          /**< Color del borde mytuiContainer#border. */
    int closeColor;      /**< Color botón de cerrar mytuiContainer#coloseColor.
                          */
    int minimizeColor;   /**< color del icono de minimizar
                            mytuiContainer#minimize.*/
    ContainerTypes type; /**<typo de contenedor mytuiContainer#type. */
    struct ChildContainer *childContainer;
};

void mytui_inicialize_container(MytuiContainer **stance, MytuiContainerParam param)
{
    if (*stance != NULL) {
        print_error("mytui_inicialize_container: el container debe ser "
                    "null");
    }
    *stance = (MytuiContainer *)malloc(sizeof(MytuiContainer));
    (*stance)->bg = param.bg;
    (*stance)->x = param.x;
    (*stance)->y = param.y;
    (*stance)->h = param.h;
    (*stance)->w = param.w;
    (*stance)->border = param.border;
    (*stance)->type = param.type;
    (*stance)->closeColor = param.closeColor;
    (*stance)->minimizeColor = param.minimizeColor;
    (*stance)->decoration = param.decoration;
    (*stance)->childContainer = NULL;
}

void update_MytuiContainer(MytuiContainer *container)
{
    if (container == NULL) {
        print_error("update_MytuiContainer: "
                    "No se puede inicializar un Entry en NULL");
    }
    NodeTranformation *node = NULL;

    // evaluacion del container bg
    char *container_bg;
    if (container->bg < 0) {
        container_bg = resolve_value(_confMap, "container.bg", NULL);
    } else {
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->bg);
        container_bg = resolve_value(_confMap, "container.bg", buffer_str);
    }

    if (!strIsInt(container_bg)) {
        print_error("update_MytuiContainer: valor container.bg debe "
                    "ser entero: %s",
                    container_bg);

        // print_info("El valor es de : strIsInt %d , container_bg %s",
        // strIsInt(container_bg), container_bg);
    }

    unsigned int container_bg_int = atoi(container_bg);
    // end evaluacion del container bg

    // evaluacion del container close
    char *container_close_color;
    if (container->closeColor < 0) {
        container_close_color = resolve_value(_confMap, "container.close", NULL);
    } else {
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->bg);
        container_close_color = resolve_value(_confMap, "container.close", buffer_str);
    }
    if (!strIsInt(container_close_color)) {
        print_error("update_MytuiContainer: valor"
                    "container.close debe ser entero");
    }
    unsigned int container_close_color_int = atoi(container_close_color);
    // end evaluacion del container close color

    // evaluacion del container close
    char *container_minimize_color;
    if (container->minimizeColor < 0) {
        container_minimize_color = resolve_value(_confMap, "container.minimize", NULL);
    } else {
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->minimizeColor);
        container_close_color = resolve_value(_confMap, "container.minimize", buffer_str);
    }
    if (!strIsInt(container_minimize_color)) {
        print_error("update_MytuiContainer: valor"
                    "container.minimize debe ser entero");
    }
    unsigned int container_minimize_color_int = atoi(container_minimize_color);
    // end evaluacion del container close color

    // evaluacion del container border
    char *container_border;
    if (container->border < 0) {
        container_border = resolve_value(_confMap, "container.border", NULL);
    } else {
        char buffer_str[255];
        sprintf(buffer_str, "%d", container->border);
        container_border = resolve_value(_confMap, "container.border", buffer_str);
    }
    if (!strIsInt(container_border)) {
        print_error("update_MytuiContainer: valor container.bg debe "
                    "ser entero");
    }
    unsigned int container_border_int = atoi(container_border);
    // end evaluacion del container border

    if (container->type == MYTUI_CONTAINER_ROOT) {
        struct InfoTerm infoTerm = get_info_term();
        container->x = 0;
        container->y = 0;
        container->w = infoTerm.width;
        container->h = infoTerm.height;
    }

    for (int i = container->y; i < (container->h + container->y); i++) {
        for (int j = container->x; j < (container->w + container->x); j++) {
            if (container->decoration == true) {
                if (i == container->y || i == (container->h + container->y) - 1) {
                    // caracter de la decoracion
                    uint32_t decoration = ' ';

                    // para agregar extra colores como para
                    // el cerrar manimizar
                    unsigned int resolution_extra_color = container_bg_int;

                    // iconos de cerrar agrandar para la
                    // ventana
                    if (container->type == MYTUI_CONTAINER_WIN &&
                        (container->w + container->x) - 2 == j && i == container->y) {
                        decoration = 0x2591;
                        resolution_extra_color = container_close_color_int;

                    } else if (container->type == MYTUI_CONTAINER_WIN &&
                               (container->w + container->x) - 3 == j && i == container->y) {
                        decoration = 0x2591;
                        resolution_extra_color = container_minimize_color_int;

                    } else if (j == container->x && i == container->y) {
                        //┌
                        decoration = 0x250C;
                    } else if ((container->w + container->x) - 1 == j && i == container->y) {
                        //┐
                        decoration = 0x2510;
                    } else if (j == container->x && (container->h + container->y) - 1) {
                        //└
                        decoration = 0x2514;
                    } else if ((container->w + container->x) - 1 == j &&
                               (container->h + container->y) - 1) {
                        //┘
                        decoration = 0x2518;
                    } else {
                        //─
                        decoration = 0x2500;
                    }
                    nodeTranformation_add(&node, j, i, resolution_extra_color, container_border_int,
                                          decoration);

                } else if (j == container->x || j == (container->w + container->x) - 1) {
                    //'|'
                    nodeTranformation_add(&node, j, i, container_bg_int, container_border_int,
                                          0x2502);
                } else {
                    nodeTranformation_add(&node, j, i, container_bg_int, MYTUI_COLOR_DEFAULT, ' ');
                }
            } else {
                nodeTranformation_add(&node, j, i, container_bg_int, MYTUI_COLOR_DEFAULT, ' ');
            }
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}

void free_mytui_container(MytuiContainer **stance)
{
    printf("%p que es \n", *stance);
    if (*stance != NULL) {

        while ((*stance)->childContainer != NULL) {

            ChildContainer *tmpChildContainer = (*stance)->childContainer->next;

            ChildContainerWidget *tmpChildContainerWidget =
                (*stance)->childContainer->childContainerWidgetFront;

            if (tmpChildContainerWidget != NULL) {

                while ((*stance)->childContainer->childContainerWidgetFront != NULL) {

                    if (tmpChildContainerWidget->next != NULL) {

                        tmpChildContainerWidget = tmpChildContainerWidget->next;

                        free_MyTuiWidget(&(*stance)->childContainer->childContainerWidgetFront->widget);
                        free((*stance)->childContainer->childContainerWidgetFront);

                        (*stance)->childContainer->childContainerWidgetFront =
                            tmpChildContainerWidget;

                    } else {

                        free_MyTuiWidget(&(*stance)->childContainer->childContainerWidgetFront->widget);
                        free((*stance)->childContainer->childContainerWidgetFront);
                        (*stance)->childContainer->childContainerWidgetFront = NULL;
                        (*stance)->childContainer->childContainerWidget = NULL;
                    }
                }
            }

            free((*stance)->childContainer);
            (*stance)->childContainer = tmpChildContainer;
        }
        free(*stance);
    }
}

void add_ChildContainer(MytuiContainer **stance)
{
    if ((*stance)->childContainer == NULL) {
        (*stance)->childContainer = (ChildContainer *)malloc(sizeof(ChildContainer));
        (*stance)->childContainer->next = NULL;
        (*stance)->childContainer->childContainerWidget = NULL;
    } else {
        ChildContainer *tmp_old = (*stance)->childContainer;

        ChildContainer *tmpChildContainer = (ChildContainer *)malloc(sizeof(ChildContainer));

        (*stance)->childContainer = tmpChildContainer;

        (*stance)->childContainer->childContainerWidget = NULL;

        (*stance)->childContainer->next = tmp_old;
    }
}

void add_childContainerWidget(MytuiContainer **mytuiContainer, float margin_top, float margin_left,
                              float margin_bottom, float margin_right, MiTuiWidget **miTuiWidget)
{

    if ((*mytuiContainer)->childContainer == NULL) {
        print_error("add_childContainerWidget: childContainerWidget no "
                    "puede"
                    " ser null");
    }

    if ((*miTuiWidget) == NULL) {
        print_error("add_childContainerWidget: miTuiWidget no puede "
                    "ser NULL");
    }

    if ((*mytuiContainer)->childContainer->childContainerWidget == NULL) {

        ChildContainerWidget *containerWidget =
            (ChildContainerWidget *)malloc(sizeof(ChildContainerWidget));
        containerWidget->margin_bottom = margin_bottom;
        containerWidget->margin_left = margin_left;
        containerWidget->margin_top = margin_top;
        containerWidget->margin_right = margin_right;
        containerWidget->widget = (*miTuiWidget);
        containerWidget->next = NULL;

        (*mytuiContainer)->childContainer->childContainerWidget = containerWidget;
        (*mytuiContainer)->childContainer->childContainerWidgetFront =
            (*mytuiContainer)->childContainer->childContainerWidget;

    } else {

        ChildContainerWidget *tmpContainerWidget =
            (ChildContainerWidget *)malloc(sizeof(ChildContainerWidget));

        (*mytuiContainer)->childContainer->childContainerWidget->next = tmpContainerWidget;

        tmpContainerWidget->margin_bottom = margin_bottom;
        tmpContainerWidget->margin_left = margin_left;
        tmpContainerWidget->margin_top = margin_top;
        tmpContainerWidget->margin_right = margin_right;
        tmpContainerWidget->widget = (*miTuiWidget);
        tmpContainerWidget->next = NULL;

        (*mytuiContainer)->childContainer->childContainerWidget = tmpContainerWidget;
    }
}

void update_MytuiContainer_childContainer(MytuiContainer *container)
{
    ChildContainer *childContainer = container->childContainer;

    struct InfoTerm infoTerm = get_info_term();

    while (childContainer != NULL) {

        int counter_container_height = 0;
        ChildContainerWidget *beforeChildContainerWidget = NULL;

        ChildContainerWidget *tmpChildContainerWidget =
            container->childContainer->childContainerWidgetFront;

        while (tmpChildContainerWidget != NULL) {

            if (tmpChildContainerWidget->widget != NULL) {

                // CONTAINER_ROT
                if (container->type == MYTUI_CONTAINER_ROOT) {
                    tmpChildContainerWidget->widget->x = tmpChildContainerWidget->margin_right;

                    if (beforeChildContainerWidget != NULL) {
                        counter_container_height += tmpChildContainerWidget->margin_bottom;
                    }

                    tmpChildContainerWidget->widget->y =
                        counter_container_height + tmpChildContainerWidget->margin_top;

                    if (tmpChildContainerWidget->widget->type == mytuiLabel &&
                        tmpChildContainerWidget->widget->w != -1) {
                    } else {
                        tmpChildContainerWidget->widget->w = infoTerm.width -
                                                             tmpChildContainerWidget->margin_left -
                                                             tmpChildContainerWidget->margin_right;
                    }

                    counter_container_height +=
                        tmpChildContainerWidget->widget->h + tmpChildContainerWidget->margin_top;
                    update_MyTuiWidget(tmpChildContainerWidget->widget);
                } // end container root
            }

            tmpChildContainerWidget = tmpChildContainerWidget->next;
        }

        childContainer = childContainer->next;
    }
}
