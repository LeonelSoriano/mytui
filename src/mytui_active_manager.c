#include "mytui_active_manager.h"

static MytuiActiveWidget *_mytuiActiveWidget = NULL;


/*    "button.active=237",
    "button.fg-active=237",
*/
void change_active_miTuiWidget(MiTuiWidget *miTuiWidget){
    if(_mytuiActiveWidget == NULL){
        _mytuiActiveWidget = (MytuiActiveWidget *)malloc(sizeof(MytuiActiveWidget));
        _mytuiActiveWidget->bc = miTuiWidget->bc;
        _mytuiActiveWidget->fc = miTuiWidget->fc;
        _mytuiActiveWidget->miTuiWidget = miTuiWidget;
        //cambiar aca los colores de selecionado depende el tipo


        switch (_mytuiActiveWidget->miTuiWidget->type) {
            case mytuiButton:
print_line_log(MytuiLoggerTypeError, "aca");
                _mytuiActiveWidget->miTuiWidget->bc = resolve_color(_confMap, -1 , "button.active");
                _mytuiActiveWidget->miTuiWidget->fc = resolve_color(_confMap, -1 , "button.fg-active");
                break;
        }




    }else{
        _mytuiActiveWidget->miTuiWidget->fc = _mytuiActiveWidget->fc;
        _mytuiActiveWidget->miTuiWidget->bc = _mytuiActiveWidget->bc;
        _mytuiActiveWidget->miTuiWidget = miTuiWidget;
        //cambiar aca los colores de selecionado depende el tipo

    }

}


void delete_active_miTuiWidget(){
    if(_mytuiActiveWidget != NULL){
        free(_mytuiActiveWidget);
    }
}
