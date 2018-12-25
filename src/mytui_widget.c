#include "mytui_widget.h"

void init_MyTuiWidgetEntry(MiTuiWidget** widget, int x, int y, int w, int h,
 int bc){
    *widget = (MiTuiWidget*)malloc(sizeof(MiTuiWidget));
    (*widget)->type = entry;
    (*widget)->h = h;
    (*widget)->w = w;
    (*widget)->y = y;
    (*widget)->x = x;
    (*widget)->bc = bc;
}

void update_MyTuiWidgetEntry(MiTuiWidget* widget){
    if (widget == NULL) {
        print_error("update_MyTuiWidgetEntry: No se puede inicializar un Entry en NULL");
    }
    NodeTranformation* node = NULL;

    const char* bg_str = resolve_value(_confMap, "entry.bg", NULL);

    unsigned int bg = 0;

    //validaciones para datos de entrada
    if (strIsInt(bg_str) == true) {
        bg = atoi(bg_str);
        if (bg > MAX_COLORS_VALUES) {
            char* std_value = find_std_values("entry.bg");
            bg = atoi(std_value);
        }
    } else {
        //si tiene mal el valor en conf sera el por defecto
        bg = MYTUI_COLOR_DEFAULT;
    }

    for (int i = widget->y; i < (widget->h + widget->y); i++) {
        for (int j = widget->x; j < (widget->w + widget->x); j++) {
            nodeTranformation_add(&node, j, i, bg, MYTUI_COLOR_DEFAULT, ' ');
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}

void free_MyTuiWidgetEntry(MiTuiWidget** widget){
    if (*widget != NULL) {
        free(*widget);
    }
}
