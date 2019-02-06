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

static void _update_MyTuiWidgetLabel(MiTuiWidget *widget)
{
    NodeTranformation *node = NULL;

    int bc_color = resolve_color(_confMap, widget->bc, "label.bg");

    int fc_color = resolve_color(_confMap, widget->fc, "label.fg");

    MiTuiWidgetExtraLabel *extra = (MiTuiWidgetExtraLabel *)widget->extra;

    int str_size = strlen(extra->text);

    int draw_x = (widget->w < str_size) ? str_size : widget->w;

    for (int i = widget->y; i < (widget->h + widget->y); i++) {

        int character_line = 0;

        for (int j = widget->x; j < (draw_x + widget->x); j++) {

            // si el carácter es igual a la linea uno y
            // en menor al string para evitar over flow
            if (i == widget->y && character_line < str_size) {
                nodeTranformation_add(&node, j, i, bc_color, fc_color, extra->text[character_line]);
            } else {
                nodeTranformation_add(&node, j, i, bc_color, MYTUI_COLOR_DEFAULT, ' ');
            }
            character_line++;
        }
    }
    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}

/*    "button.bg=237",
    "button.fg=237",
    "button.active=237",
    "button.fg-active=237",
    "button.shadow=237",
*/
//char *text, int x, int y, int w, int h, int bc, int fc,int shadow
static void _update_MyTuiWidgetButton(MiTuiWidget *widget){

    NodeTranformation *node = NULL;

    MiTuiWidgetExtraButton *extra = (MiTuiWidgetExtraButton*) widget->extra;

    int bc_color = resolve_color(_confMap, widget->bc, "button.bg");
    int fc_color = resolve_color(_confMap, widget->fc, "button.fg");
    int active_color = resolve_color(_confMap, extra->active , "button.active");
    int fg_active_color = resolve_color(_confMap, extra->active , "button.fg-active");
    int shadow_color = resolve_color(_confMap, extra->active , "button.shadow");

    int str_size = strlen(extra->text);
    int draw_x = (widget->w < str_size) ? str_size : widget->w;

    for (int i = widget->y; i < (widget->h + widget->y); i++) {

        int character_line = 0;

        for (int j = widget->x; j < (draw_x + widget->x); j++) {

            // si el carácter es igual a la linea uno y
            // en menor al string para evitar over flow
            if (i == widget->y && character_line < str_size) {
                nodeTranformation_add(&node, j, i, bc_color, fc_color, extra->text[character_line]);
            } else {
                nodeTranformation_add(&node, j, i, bc_color, MYTUI_COLOR_DEFAULT, ' ');
            }
            character_line++;
        }
    }
    if(widget->h > 1){
        for (int i = widget->y +1; i < (widget->h + widget->y); i++) {
            nodeTranformation_add(&node, (draw_x + widget->x), i, shadow_color, MYTUI_COLOR_DEFAULT, ' ');
        }
        for (int i = widget->x+1; i < (draw_x + widget->x) + 1; i++) {
            nodeTranformation_add(&node, i, (widget->h + widget->y), shadow_color, MYTUI_COLOR_DEFAULT, ' ');
        }
    }

    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}


MiTuiWidget *init_MyTuiWidgetEntry(int x, int y, int w, int h, int bc)
{
    MiTuiWidget *widget = (MiTuiWidget *)malloc(sizeof(MiTuiWidget));
    widget->type = mytuiEntry;
    widget->h = h;
    widget->w = w;
    widget->y = y;
    widget->x = x;
    widget->bc = bc;
    return widget;
}

MiTuiWidget *init_MyTuiWidgetLabel(char *text, int x, int y, int w, int h, int bc, int fc)
{
    MiTuiWidget *widget = (MiTuiWidget *)malloc(sizeof(MiTuiWidget));
    widget->type = mytuiLabel;
    widget->h = h;
    widget->w = w;
    widget->y = y;
    widget->x = x;
    widget->bc = bc;
    widget->fc = fc;

    MiTuiWidgetExtraLabel *extra = (MiTuiWidgetExtraLabel *)malloc(sizeof(MiTuiWidgetExtraLabel));
    extra->text = malloc(strlen(text) + 1);
    ;
    strcpy(extra->text, text);
    widget->extra = extra;
    return widget;
}

MiTuiWidget *init_MyTuiWidgetButton(char *text, int x, int y, int w, int h, int bc, int fc,
                                    int shadow)
{
    MiTuiWidget *widget = (MiTuiWidget *)malloc(sizeof(MiTuiWidget));
    widget->type = mytuiButton;
    widget->h = h;
    widget->w = w;
    widget->y = y;
    widget->x = x;
    widget->bc = bc;
    widget->fc = fc;

    MiTuiWidgetExtraButton *extra =
        (MiTuiWidgetExtraButton *)malloc(sizeof(MiTuiWidgetExtraButton));
    extra->text = malloc(strlen(text) + 1);
    ;
    strcpy(extra->text, text);
    extra->shadow = shadow;
    extra->active = -1;
    extra->shadow = -1;
    extra->shadowActive = true;
    widget->extra = extra;
    return widget;
}

void update_MyTuiWidget(MiTuiWidget *widget)
{
    if (widget == NULL) {
        print_error("update_MyTuiWidget: No se puede inicializar un Entry "
                    "en NULL");
    }
    switch (widget->type) {
    case mytuiEntry:
        _update_MyTuiWidgetEntry(widget);
        break;
    case mytuiLabel:
        _update_MyTuiWidgetLabel(widget);
        break;
    case mytuiButton:
        _update_MyTuiWidgetButton(widget);
        break;
    }
}

void free_MyTuiWidget(MiTuiWidget **widget)
{
    if ((*widget)->type == mytuiLabel) {

        MiTuiWidgetExtraLabel *extra = (MiTuiWidgetExtraLabel *)(*widget)->extra;
        free(extra->text);
        free(extra);
    }else if((*widget)->type == mytuiButton){
        MiTuiWidgetExtraButton *extra = (MiTuiWidgetExtraButton *)(*widget)->extra;
        free(extra->text);
        free(extra);
    }

    if (*widget != NULL) {
        free(*widget);
    }
}




static void _clean_MyTuiWidgetButton(MiTuiWidget *widget){
    NodeTranformation *node = NULL;
    MiTuiWidgetExtraButton *extra = (MiTuiWidgetExtraButton*) widget->extra;

    int str_size = strlen(extra->text);
    int draw_x = (widget->w < str_size) ? str_size : widget->w;

    for (int i = widget->y; i < (widget->h + widget->y); i++) {

        int character_line = 0;

        for (int j = widget->x; j < (draw_x + widget->x); j++) {
            nodeTranformation_add(&node, j, i, MYTUI_COLOR_DEFAULT, MYTUI_COLOR_DEFAULT, ' ');
            character_line++;
        }
    }
    if(widget->h > 1){
        for (int i = widget->y +1; i < (widget->h + widget->y); i++) {
            nodeTranformation_add(&node, (draw_x + widget->x), i, MYTUI_COLOR_DEFAULT, MYTUI_COLOR_DEFAULT, ' ');
        }
        for (int i = widget->x+1; i < (draw_x + widget->x) + 1; i++) {
            nodeTranformation_add(&node, i, (widget->h + widget->y), MYTUI_COLOR_DEFAULT, MYTUI_COLOR_DEFAULT, ' ');
        }
    }

    node_bufffer_vs_tranformator(&nodeBufer, node);
    nodeTranformation_free(&node);
}


void clean_MyTuiWidget(MiTuiWidget *widget, MytuiContainer *stance){

    if (widget == NULL) {
        print_error("update_MyTuiWidget: No se puede inicializar un Entry "
                    "en NULL");
    }
    switch (widget->type) {
    case mytuiEntry:
    //    _update_MyTuiWidgetEntry(widget);
        break;
    case mytuiLabel:
//        _update_MyTuiWidgetLabel(widget);
        break;
    case mytuiButton:

        _clean_MyTuiWidgetButton(widget);
        break;
    }


}


