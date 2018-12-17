#include "mytui_widget.h"

void init_MyTuiWidgetEntry(MiTuiWidget ** widget, int x, int y, int w, int h, int bc){
    *widget = (MiTuiWidget*)malloc(sizeof(MiTuiWidget));
    (*widget)->type = entry;
    (*widget)->h = h;
    (*widget)->w = w;
    (*widget)->y = y;
    (*widget)->x = x;
    (*widget)->bc = bc;
}


void update_MyTuiWidgetEntry(MiTuiWidget *widget){
    if(widget == NULL){
        print_error("update_MyTuiWidgetEntry: No se puede inicializar un Entry en NULL");
    }
    NodeTranformation *node = NULL;

    for(int i = widget->y; i < (widget->h + widget->y) ; i++){

        for(int j = widget->x; j < (widget->w + widget->x); j++){
            nodeTranformation_add(&node, j, i, 12,2);
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}
