#include "mytui_widget.h"



/**
 * interna de dibujado de Entry
 * @see init_mytui
 */
static void _update_MyTuiWidgetEntry(MiTuiWidget *widget)
{
    NodeTranformation *node = NULL;

    char *bg_str;

    unsigned int bg = widget->bc;
    if (widget->bc < 0) {
        bg_str = resolve_value(_confMap, "entry.bg", NULL);
    } else {
        char buffer_str[255];
        sprintf(buffer_str, "%d", widget->bc);
        bg_str = resolve_value(_confMap, "entry.bg", buffer_str);
    }

    if (strIsInt(bg_str) == true) {

        bg = atoi(bg_str);

        if (bg > MAX_COLORS_VALUES) {
            char *std_value = find_std_values("entry.bg");
            bg = atoi(std_value);
        }
    } else {
        // si tiene mal el valor en conf sera el por defecto
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

static void _update_MyTuiWidgetLabel(MiTuiWidget *widget){
    NodeTranformation *node = NULL;

    int bc_color = resolve_color(_confMap, widget->bc,"label.bg");

    int fc_color = resolve_color(_confMap, widget->fc,"label.fg");

    MiTuiWidgetExtraLabel* extra = (MiTuiWidgetExtraLabel*) widget->extra;

    int str_size = strlen(extra->text);

    int draw_x = (widget->w < str_size)? str_size: widget->w;

    for (int i = widget->y; i < (widget->h + widget->y); i++) {

        int character_line = 0;

        for (int j = widget->x; j < (draw_x + widget->x); j++) {

            //si el caracter es igual a la linea uno y
            // en menor al string para evitar over flow
            if(i == widget->y && character_line <  str_size){
                nodeTranformation_add(&node, j, i, bc_color, fc_color,
                        extra->text[character_line]);
            }else{
                nodeTranformation_add(&node, j, i, bc_color,
                        MYTUI_COLOR_DEFAULT, ' ');
            }
            character_line++;
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}


MiTuiWidget *init_MyTuiWidgetEntry(int x, int y, int w, int h, int bc)
{
    MiTuiWidget *widget = (MiTuiWidget *)malloc(sizeof(MiTuiWidget));
    widget->type = entry;
    widget->h = h;
    widget->w = w;
    widget->y = y;
    widget->x = x;
    widget->bc = bc;
    return widget;
}


MiTuiWidget* init_MyTuiWidgetLabel(char *text, int x, int y, int w, int h,
                                  int bc, int fc)
{
    MiTuiWidget *widget = (MiTuiWidget *)malloc(sizeof(MiTuiWidget));
    widget->type = label;
    widget->h = h;
    widget->w = w;
    widget->y = y;
    widget->x = x;
    widget->bc = bc;
    widget->fc = fc;

    MiTuiWidgetExtraLabel* extra = (MiTuiWidgetExtraLabel*)malloc(sizeof(MiTuiWidgetExtraLabel));
    extra->text = malloc(strlen(text) + 1); ;
    strcpy(extra->text, text);
    widget->extra = extra;
    return widget;
}

void update_MyTuiWidget(MiTuiWidget *widget)
{
    if (widget == NULL) {
        print_error("update_MyTuiWidget: No se puede inicializar un Entry "
                    "en NULL");
    }
    switch(widget->type){
        case entry:
            _update_MyTuiWidgetEntry(widget);
            break;
        case label:
            _update_MyTuiWidgetLabel(widget);
            break;
    }

}

void free_MyTuiWidget(MiTuiWidget **widget)
{
    if((*widget)->type == label){
        MiTuiWidgetExtraLabel* extra = (MiTuiWidgetExtraLabel*)(*widget)->extra;
        free(extra->text);
        free((*widget)->extra);
    }

    if (*widget != NULL) {
        free(*widget);
    }
}
