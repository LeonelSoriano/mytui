#include "mytui_active_manager.h"

static MytuiActiveWidget *_mytuiActiveWidget = NULL;


static void resolve_type_widget(MytuiActiveWidget *mytuiActiveWidget){
    switch (mytuiActiveWidget->miTuiWidget->type) {
        case mytuiButton:

            _mytuiActiveWidget->miTuiWidget->bc = resolve_color(_confMap, -1 , "button.active");
            _mytuiActiveWidget->miTuiWidget->fc = resolve_color(_confMap, -1 , "button.fg-active");
            break;
        case mytuiTextBox:


            _mytuiActiveWidget->miTuiWidget->bc = resolve_color(_confMap, -1 , "tex.active");
            _mytuiActiveWidget->miTuiWidget->fc = resolve_color(_confMap, -1 , "button.fg-active");
            break;
    }
}

void change_active_miTuiWidget(MiTuiWidget *miTuiWidget){

    if(_mytuiActiveWidget != NULL && _mytuiActiveWidget->miTuiWidget != NULL &&
            _mytuiActiveWidget->miTuiWidget == miTuiWidget){
        //si ya esta activo ya no cambio
        return;
    }

    if(_mytuiActiveWidget == NULL){
        _mytuiActiveWidget = (MytuiActiveWidget *)malloc(sizeof(MytuiActiveWidget));
        _mytuiActiveWidget->bc = miTuiWidget->bc;
        _mytuiActiveWidget->fc = miTuiWidget->fc;
        _mytuiActiveWidget->miTuiWidget = miTuiWidget;
        //cambiar aca los colores de selecionado depende el tipo

        resolve_type_widget( _mytuiActiveWidget);


    }else{
        _mytuiActiveWidget->miTuiWidget->fc = _mytuiActiveWidget->fc;
        _mytuiActiveWidget->miTuiWidget->bc = _mytuiActiveWidget->bc;
        update_MyTuiWidget(_mytuiActiveWidget->miTuiWidget);

        _mytuiActiveWidget->miTuiWidget = miTuiWidget;

        resolve_type_widget( _mytuiActiveWidget);
        //cambiar aca los colores de selecionado depende el tipo
    }

}


void action_active_miTuiWidget(uint16_t ch, uint16_t key) {
    if(_mytuiActiveWidget == NULL || _mytuiActiveWidget->miTuiWidget == NULL){
        //si no tengo activos
        return;
    }

    switch (_mytuiActiveWidget->miTuiWidget->type) {
        case mytuiTextBox:
        {

            MiTuiWidgetExtraTextBox *extra = (MiTuiWidgetExtraTextBox*) _mytuiActiveWidget->miTuiWidget->extra;
            size_t text_len = strlen(extra->text);

            if (key == 127 && text_len > 0) {
                size_t new_len = text_len -1;
                char newText[new_len + 1];
                for (size_t i = 0; i < new_len; ++i) {
                    newText[i] = extra->text[i];
                }

                newText[new_len ] = '\0';
                set_text_MyTuiWidgetTextBox(_mytuiActiveWidget->miTuiWidget, newText);
                update_MyTuiWidget(_mytuiActiveWidget->miTuiWidget);

            } else {


                char newText[ text_len + 2];
                strcpy(newText, extra->text);

                newText[text_len ++] = ch;
                newText[text_len ++] = '\0';

                set_text_MyTuiWidgetTextBox(_mytuiActiveWidget->miTuiWidget, newText);
                update_MyTuiWidget(_mytuiActiveWidget->miTuiWidget);
            }

            break;
        }
    }



}


void delete_active_miTuiWidget(){
    if(_mytuiActiveWidget != NULL){
        free(_mytuiActiveWidget);
    }
}
