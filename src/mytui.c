#include "mytui.h"

static void _init_termbox(){
    int ret = tb_init();
    if (ret) {
        print_error("_init_termbox: errror al iniciar terbox ");
        exit(EXIT_FAILURE);
    }
    //tb_select_input_mode( TB_INPUT_MOUSE);
    tb_select_output_mode(TB_OUTPUT_NORMAL);
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
    static int a = 0;
    struct tb_event ev;
    while (tb_poll_event(&ev)) {
        switch (ev.type) {
            case TB_EVENT_KEY:
                switch (ev.key) {
                    case TB_KEY_ESC:
                        tb_shutdown();
                        exit(EXIT_SUCCESS);

                    case TB_KEY_CTRL_A:{
                        NodeTranformation *node = NULL;
                        nodeTranformation_add(&node, 0, 0, 1,1);
                        node_bufffer_vs_tranformator(&nodeBufer, node);
                        nodeTranformation_free(&node);
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


