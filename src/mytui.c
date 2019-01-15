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

static void _init_termbox()
{
    int ret = tb_init();
    if (ret) {
        print_error("_init_termbox: errror al iniciar terbox ");
        exit(EXIT_FAILURE);
    }
    // tb_select_input_mode( TB_INPUT_MOUSE);
    tb_select_output_mode(TB_OUTPUT_256);
}

static void _free_termbox() { tb_shutdown(); }

/*inicia todo*/
void init_mytui()
{
    nodeBufer = NULL;
    // hash_conf = NULL;
    ini_conf_file();
    load_conf_map(&_confMap);

    // print_info("resolve value que es: %s",resolve_value(_confMap,"entry.bg",NULL) );

    init_buffer(&nodeBufer);
    _init_termbox();
    screen_manager(&nodeBufer);
}

void end_mytui()
{
    _free_termbox();
    free_conf_map(&_confMap);
    free_buffer(&nodeBufer);
}

void update_termbox()
{
    struct tb_event ev;
    while (tb_poll_event(&ev)) {
        switch (ev.type) {
        case TB_EVENT_KEY:
            switch (ev.key) {
            case TB_KEY_ESC:
                end_mytui();
                exit(EXIT_SUCCESS);

            case TB_KEY_CTRL_A: {

 /*               MiTuiWidget* widget;

                init_MyTuiWidgetEntry(&widget, 1, 1, 8, 8, 1);
                update_MyTuiWidgetEntry(widget);

                free_MyTuiWidgetEntry(&widget);

                MytuiContainer* stance = NULL;

                INIT_MYTUI_CONTAINER(type);

           //     type.type = MYTUI_CONTAINER_ROOT;
                type.type = MYTUI_CONTAINER_WIN;
                type.w = 20;
                type.h = 10;
                type.x = 30;
                type.y = 20;
                type.decoration = true;

                mytui_inicialize_container(&stance, type);
                update_MytuiContainer(stance);
                free_mytui_container(&stance);
*/


                MytuiContainer* mytuiContainer = NULL;
                INIT_MYTUI_CONTAINER(paramContainer);
                paramContainer.type = MYTUI_CONTAINER_ROOT;
                paramContainer.decoration = true;
                mytui_inicialize_container(&mytuiContainer, paramContainer);
                add_ChildContainer(&mytuiContainer);

                MiTuiWidget* widget;
                init_MyTuiWidgetEntry(&widget, 1, 1, 2, 8, -1);

                //update_MyTuiWidgetEntry(widget);

                add_childContainerWidget(&mytuiContainer,0,1,1,3,&widget);


                MiTuiWidget* widget2;
                init_MyTuiWidgetEntry(&widget2, 1, 1, 8, 8, 5);


                add_childContainerWidget(&mytuiContainer,1,1,1,2,&widget2);


                //el update
                //update_MytuiContainer(mytuiContainer);
                update_MytuiContainer_childContainer(mytuiContainer);

                free_mytui_container(&mytuiContainer);

                screen_manager(&nodeBufer);
                break;
            }
            }
            break;
        case TB_EVENT_RESIZE:
//            init_screen_manager(&nodeBufer);
            break;
        }
    }
}
