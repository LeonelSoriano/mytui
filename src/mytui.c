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
    tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
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

    // print_info("resolve value que es:
    // %s",resolve_value(_confMap,"entry.bg",NULL) );

    init_mytui_logger();
    init_buffer(&nodeBufer);
    _init_termbox();
    screen_manager(&nodeBufer);
}

void end_mytui()
{
    _free_termbox();
    free_conf_map(&_confMap);
    free_mytui_logger();
    free_buffer(&nodeBufer);
    delete_mytui_listener_all();
}

void update_termbox()
{
    struct tb_event ev;
    while (tb_poll_event(&ev)) {
        switch (ev.type) {

        case TB_EVENT_MOUSE:
            if (ev.key == TB_KEY_MOUSE_LEFT) {
                //				mx = ev.x;
                //				my = ev.y;
                print_error("mouse: %d , %d ", ev.x, ev.y);
                mouse_manager_event_fire(ev.x, ev.y);
            }
            break;
        case TB_EVENT_KEY:
            switch (ev.key) {
            case TB_KEY_ESC:
                end_mytui();
                exit(EXIT_SUCCESS);

            case TB_KEY_CTRL_A: {

                MytuiContainer *mytuiContainer = NULL;
                INIT_MYTUI_CONTAINER(paramContainer);
                paramContainer.type = MYTUI_CONTAINER_ROOT;
                paramContainer.decoration = true;
                mytui_inicialize_container(&mytuiContainer, paramContainer);
                add_ChildContainer(&mytuiContainer);

                MiTuiWidget *label = init_MyTuiWidgetLabel("leonelsoriano", 0, 0, -1, 1, -1, -1);
                add_childContainerWidget(&mytuiContainer, 2, 1, 0, 1, &label);





                print_line_log("hola %d", 1988);

                print_line_log("hola %d", 1981);
                print_line_log("hola %d", 1982);

                print_line_log("hola %d", 1983);


                print_line_log("hola %d", 1983);



                // el update
                update_MytuiContainer_childContainer(mytuiContainer);
                add_mytui_event_listener(NULL, mytuiEventTypePrincipal, label);
                delete_mytui_listener(label, mytuiEventTypePrincipal);

                // init btn
                MiTuiWidget *btn = init_MyTuiWidgetButton("BTN", 10, 10, 10, 2, 3, 22, -1);
                update_MyTuiWidget(btn);

                screen_manager(&nodeBufer);

                // prueba animacion
                MytuiAnimation *animation = init_MytuiAnimation(btn);
                add_step_MytuiAnimation(&animation, mytuiAnimationMove, (double[]){-1, -1, 3, 4},
                                        0.2);
                add_step_MytuiAnimation(&animation, mytuiAnimationMove, (double[]){1, 1, 3, 4},
                                        0.2);

                update_mytuiAnimation(&animation);
                free_MytuiAnimation(&animation);

                free_MyTuiWidget(&btn);

                // fin btn

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
