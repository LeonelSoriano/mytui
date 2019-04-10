#include "mytui_active_manager.h"

static MytuiActiveWidget *_mytuiActiveWidget = NULL;


static void resolve_type_widget(MytuiActiveWidget *mytuiActiveWidget){
    switch (mytuiActiveWidget->miTuiWidget->type) {
        case mytuiButton:
//print_line_log(MytuiLoggerTypeError, "aca");
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


void delete_active_miTuiWidget(){
    if(_mytuiActiveWidget != NULL){
        free(_mytuiActiveWidget);
    }
}
