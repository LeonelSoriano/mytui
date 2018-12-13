#include "mytui.h"
/**
 * inicia terbox
 * @see init_mytui
 */
static void _init_termbox();

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

void init_mytui(){
    nodeBufer = NULL;
    //hash_conf = NULL;
    ini_conf_file();
    init_buffer(&nodeBufer);
    _init_termbox();
    screen_manager(&nodeBufer);
}

void end_mytui(){
    free_buffer(&nodeBufer);
    _free_termbox();
}

void update_termbox(){
    struct tb_event ev;
    while (tb_poll_event(&ev)) {
        switch (ev.type) {
            case TB_EVENT_KEY:
                switch (ev.key) {
                    case TB_KEY_ESC:
                        tb_shutdown();
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


