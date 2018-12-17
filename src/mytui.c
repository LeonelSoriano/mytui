#include "mytui.h"
/**
 * inicia terbox
 * @see init_mytui
 */
static void _init_termbox();

ConfMap *_confMap;
/**
 * termina y librera termbox
 * @see end_mytui
 */
static void _free_termbox();

static void _init_termbox(){
    int ret = tb_init();
    if (ret) {
        print_error("_init_termbox: errror al iniciar terbox ");
        exit(EXIT_FAILURE);
    }
    //tb_select_input_mode( TB_INPUT_MOUSE);
    tb_select_output_mode(TB_OUTPUT_256);
}

static void _free_termbox(){
    tb_shutdown();
}

/*inicia todo*/
void init_mytui(){
    nodeBufer = NULL;
    //hash_conf = NULL;
    ini_conf_file();

    load_conf_map(&_confMap);

    //print_info("valor de conf %s", getValueConf(_confMap,"entry.hola"));

    print_info("resolve value que es %s", resolve_value(_confMap,"hola","hola"));

    init_buffer(&nodeBufer);
    _init_termbox();
    screen_manager(&nodeBufer);
}

void end_mytui(){
    _free_termbox();
    free_conf_map(&_confMap);
    free_buffer(&nodeBufer);

}

void update_termbox(){
    struct tb_event ev;
    while (tb_poll_event(&ev)) {
        switch (ev.type) {
            case TB_EVENT_KEY:
                switch (ev.key) {
                    case TB_KEY_ESC:
                        end_mytui();
                        exit(EXIT_SUCCESS);

                    case TB_KEY_CTRL_A:{
                        MiTuiWidget *widget;

                        init_MyTuiWidgetEntry(&widget, 1, 1, 8, 8, 1);
                        update_MyTuiWidgetEntry(widget);
                        screen_manager(&nodeBufer);
                        break;
                    }
                }
                break;
            case TB_EVENT_RESIZE:
                init_screen_manager(&nodeBufer);
                break;
        }
    }
}


